import re as regex
import json

def getkey(val:str,dict:dict):
    for key,value in dict.items():
        if val==value:
            return key

input=open('pass1\input.asm','r')
mdt=open('pass1\output\mdt.txt','w')

pattern=r'\s+'

msign=False
mdef=False

mnt={}
pntab={}
kpdtab={}

macroname=''
kpdtabindex=1
kpdtabloc=1
mntindex=1
mdtloc=1

for line in input:

    if line=='\n':continue
    line=line.strip()

    cmd=regex.split(pattern,line.rstrip())

    if len(cmd)==1 and cmd[0]=='MACRO':
        msign=True
        continue

    if msign:
        macroname=cmd.pop(0)
        pntab[macroname]={}
        paramcnt=0
        pp=0
        kp=0


        for param in cmd:

            if ',' in param:
                param=param.replace(',',"")
            
            if '&' in param and '=' not in param:
                pp+=1
                paramcnt+=1
                paramname=param[1::]

                pntab[macroname][paramcnt]=paramname
            elif '&' in param and '=' in param:

                paramcnt+=1

                if kp==0:
                    kpdtabloc=kpdtabindex
                kp+=1

                eq=param.index('=')
                paramname=param[1:eq:]
                paramdef=param[eq+1::]

                pntab[macroname][paramcnt]=paramname

                kpdtab[kpdtabindex]={
                    'index':kpdtabindex,
                    'name':paramname,
                    'value':paramdef if paramdef else '---'
                }
                kpdtabindex+=1

            else:
                pass
        msign=False
        mdef=True
        mnt[mntindex]={
            'index':mntindex,
            'name':macroname,
            'pp':pp,
            'kp':kp,
            'mdtp':mdtloc,
            'kpdtp':kpdtabloc if kp else'---'
        }

        mntindex+=1
        continue

    if mdef:
        mdtloc+=1
        calline=""

        for command in cmd:
            #print(command)
            if ',' in command:
                command=command.replace(',','')
            if '&' in command:
                value=f'(P,{getkey(command[1::],pntab[macroname])})'
                calline+=value+" "
            else:
                calline+=command+" "
        mdt.write(calline+'\n')
        continue

    if len(cmd)==1 and cmd[0]=='MEND':
        mdtloc+=1
        mdef=False
        mdt.write('MEND\n')
        continue

with open('pass1\output\kpdtab.json','w') as j:
    json.dump(kpdtab,j,indent=4)

with open('pass1\output\pntab.json','w') as j:
    json.dump(pntab,j,indent=4)

with open('pass1\output\mnt.json','w') as j:
    json.dump(mnt,j,indent=4)