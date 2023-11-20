import re as regex
import json

symboltab=json.load(open('pass1\output\symbols.json','r'))
literaltab=json.load(open('pass1\output\literals.json','r'))
ic=open('pass1\output\ic.txt','r')
op=open('pass2\output2.txt','w')
opcode=op1code=op2code=""
lc=""
cnt=-1
pattern=r'\s+'

for line in ic:
    opcode=op1code=op2code=""
    if line=='\n':
        continue
    line=line.strip()
    ipwords=regex.split(pattern,line.rstrip())

    if len(ipwords)==4:
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        op1code=ipwords[2].replace('(',"")
        op1code=op1code.replace(')',"")
        cnt=ipwords[3].split(',')[1].replace(')',"")
        if 'S' in ipwords[3]:
            for symbol,[stcnt,symb,value] in symboltab.items():
                if stcnt==int(cnt):
                    op2code=value
        elif 'L' in ipwords[3]:
            for literal,[ltcnt,literal,value] in literaltab.items():
                if ltcnt==int(cnt):
                    op2code=value
    elif len(ipwords)==3:
        print(ipwords)
        lc=ipwords[0]
        opcode=ipwords[1].split(',')[1].replace(')',"")
        cnt=ipwords[2].split(',')[1].replace(')',"")
        if 'C' in ipwords[2]:
            op1code=cnt
        elif 'S' in ipwords[2]:
            for symbol,[stcnt,symb,value] in symboltab.items():
                if stcnt==int(cnt):
                    op1code=value
        op2code=""
    elif len(ipwords)==2:
        if 'IS' in ipwords[1]:
            lc=ipwords[0]
            opcode=ipwords[1].split(',')[1].replace(')',"")
            op1code=""
            op2code=""
        else:
            continue
    else:
        continue


    op.write(f"{lc}\t{opcode}\t{op1code}\t{op2code}\n")