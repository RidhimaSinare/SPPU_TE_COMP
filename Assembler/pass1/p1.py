import re as regex
import json

#opening files
mnemonics=json.load(open('pass1\input\mnemonics.json'))
directives=json.load(open('pass1\input\directive.json'))
conditioncodes=json.load(open('pass1\input\condition-codes.json'))
registers=json.load(open('pass1\input\\registers.json'))
program=open('pass1\input\program.asm','r')

#output files
ic=open('pass1\output\ic.txt','w')

pattern=r'\s+'

label=""
instruction=""
op1=""
op2=""
op1code=""
op2code=""
current=0
previous=0
flag=False
relativeAddress=[]
IC=[]
stcnt=1
ltcnt=1

symboltable={}
literaltable={}

for line in program:

    label=""
    instruction=""
    op1=""
    op2=""
    op1code=""
    op2code=""
    var=""  #create here

    if line =='\n':continue
    line=line.strip()

    cmd=regex.split(pattern,line.rstrip())
    cmd=list(map(lambda x:x.lower(),cmd))


    #tokenization
    if len(cmd)==4:
        label=cmd[0]
        instruction=cmd[1]
        op1=cmd[2]
        op2=cmd[3]
    
    elif len(cmd)==3:

        cmdindex=-1
        for c in cmd:
            if c in mnemonics:
                if c=="ds" or c=="dc":
                    var=cmd[0]
                    cmdindex=1
                    op1=cmd[2]
                    flag=True
                    break
                else:
                    cmdindex=cmd.index(c)
                    break
            if c in directives:
                cmdindex=cmd.index(c)
                break
        instruction=cmd[cmdindex]
        if cmdindex==0:
            op1=cmd[1]
            op2=cmd[2]
        elif flag==False:
            op1=cmd[cmdindex-1]
            op2=cmd[cmdindex+1]
    
    elif len(cmd)==2:

        cmdindex=-1
        for c in cmd:
            if c in directives or c in mnemonics:
                cmdindex=cmd.index(c)
                break
        instruction=cmd[cmdindex]
        if cmdindex==0:
            op1=cmd[1]
        else:
            label=cmd[0]
    
    else:
        instruction=cmd[0]

    #instruction matching

    if instruction in directives:
        if instruction=="start":
            current=int(cmd[1])
            opcode=directives.get(instruction)
            op1code=f"(C,{current})"
            ic.write(f"   {opcode} {op1code}\n")
            continue
        elif instruction=="end":
            opcode=directives.get(instruction)
            ic.write(f"    {opcode}")
            break
        elif instruction=="origin":
            opcode=directives.get(instruction)
            op1=cmd[1]
            if '-' in op1:
                label=op1.split('-')[0]
                offset=op1.spli('-')[1]
                op1code=f"(S,{symboltable.get(label)[0]})-{offset}"
                previous=current
                relativeAddress.append(previous)
                current=symboltable.get(label)[2]-int(offset)
                ic.write(f"     {opcode} {op1code}\n")
            elif '+' in op1:
                label=op1.split('+')[0]
                offset=op1.split('+')[1]
                op1code=f"(S,{symboltable.get(label)[0]})+{offset}"
                previous=current
                relativeAddress.append(previous)
                current=symboltable.get(label)[2]+int(offset)
                ic.write(f"     {opcode} {op1code}\n")
            else:
                op1code=f"(S,{symboltable.get(op1)[0]})"
                previous=current
                relativeAddress.append(previous)
                #current=symboltable.get(op1)[2]
                ic.write(f"     {opcode} {op1code}\n")
        elif instruction=="equ":
            op1=cmd[0]
            op2=cmd[2]
            symboltable[op1][2]=symboltable[op2][2]
        elif instruction=="ltorg":
            for literal, [index,lt,value] in literaltable.items():
                if value==-1:
                    previous=current
                    relativeAddress.append(previous)
                    current+=1

                    literaltable[literal][2]=previous
                    opcode="(DL,01)"
                    op1code=f"(C,{lt})"
                    ic.write(f"{previous} {opcode} {op1code}\n")
                else:
                    pass
                #end of checking instructions in directives
    elif instruction in mnemonics:
        if instruction=='ds':
            op2code=f""
        if instruction=='dc':
            op2code=f""
            #op1code=f"(C,{op1[1]})"
        
        opcode=mnemonics.get(instruction)
        size=1

        previous=current
        current+=size

        relativeAddress.append(previous)

        if label:
            if label in symboltable:
                    symboltable[label][2]=previous
            else:
                symboltable[label]=[stcnt,label,previous]
                stcnt+=1

        #**op1
        if instruction=='bc':
            op1code= f"({conditioncodes.get(op1)})"
        elif op1.isdigit():
            op1code=f"(C,{op1})"
        elif op1 in registers:
            op1code=f"({registers.get(op1)})"
        elif "=" in op1:
            literal=op1.split('=')[1][1]
            if op1 in literaltable:
                op1code=f"(L,{literaltable.get(op1)[0]})"
            else:
                literaltable[ltcnt]=[ltcnt,literal,-1]
                op1code=f"(L,{ltcnt})"
                ltcnt+=1
        elif instruction=='ds' or instruction=='dc':
            symboltable[op1][2]=previous
        else:
            if op1 in symboltable:
                op1code=f"(S,{symboltable.get(op1)[0]})"
            elif op1:
                symboltable[op1]=[stcnt,op1,-1]
                op1code=f"(S,{stcnt})"
                stcnt+=1
            #--end for op1
        #**op2
        if op2.isdigit():
            op2code=f"(C,{op2})"
        elif instruction=='ds' or instruction=='dc':
            symboltable[var][2]=previous
        elif op2 in registers:
            op2code=f"({registers.get(op2)})"
        elif '=' in op2:
            literal=op2.split('=')[1][1]
            if op2 in literaltable:
                op2code=f'(L,{literaltable.get(op2)[0]})'
            else:
                literaltable[ltcnt]=[ltcnt,literal,-1]
                op2code=f"(L, {ltcnt})"
                ltcnt+=1
        else:
            if op2 in symboltable:
                op2code=f"(S,{symboltable.get(op2)[0]})"
            elif op2 and instruction!='dc':
                symboltable[op2]=[stcnt,op2,-1]
                op2code=f"(S,{stcnt})"
                stcnt+=1
            #--end of processing
        if instruction!='stop':
            IC.append((opcode,op1code,op2code))
            ic.write(f"{previous} {opcode} {op1code} {op2code}\n")
        else:
            IC.append((opcode))
            ic.write(f"{previous} {opcode}\n")

    else:
        print(instruction,"Not defined")
        


#end of for

for literal, [index, lt, value] in literaltable.items():
    if value == -1:
        previous = current
        current += 1
        relativeAddress.append(previous)
        literaltable[literal][2] = previous #////////changes current to previous

        opcode = "(DL, 01)"
        op1code = f"(C, {lt})"   
        ic.write(f"{previous} {opcode} {op1code}\n")

with open("pass1\output\symbols.json","w") as json_file:
    json.dump(symboltable,json_file,indent=4)
with open("pass1\output\literals.json","w") as json_file:
    json.dump(literaltable,json_file,indent=4)

print("\nSymbol Table: ")            
symbolheaders=['symbol','id','relativeAddress']
print(f'{symbolheaders[0]: <10}{symbolheaders[1]: <15}{symbolheaders[2]}')

for key, value in symboltable.items():
    print(f'{key: <10}{value[0]: <15}{value[2]}')

print("\n\nLiteral table: ")
literalheaders=['id','literal','address']
print(f"{literalheaders[0]: <10}{literalheaders[1]: <15}{literalheaders[2]}")

for key,value in literaltable.items():
    print(f"{key: <10}{value[1]: <15}{value[2]}")
