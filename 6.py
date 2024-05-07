#expert system

#Add as many questions/function as you want

def ask_question(question: str) ->bool:

    response = input(question + ": ").lower().strip()[0]
    return response=="y"

def diagnose_fever() -> bool:

    return ask_question("Do you have temp") or ask_question("do you have chill")

def diagnose_allergies() -> bool:

    return ask_question("Do you have swelling") or ask_question("do you have red eyes")

def diagnose_cold() -> bool:

    return ask_question("Do you have stuffy nose") or ask_question("do you sneeze")


if __name__=="__main__":

    if(diagnose_fever()):
        print("you have fever")
    if(diagnose_cold()):
        print("you have cold")
    if(diagnose_allergies()):
        print("you have allergy")
