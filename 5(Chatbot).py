#chatbot

class Role:

    def __init__(self, name) -> None:
        self.name = name 
        self.responses = {}

    def add_response(self, keyword, response):
        self.responses[keyword] = response

def interact(roles):

    input_text = input("Enter your message: ")

    best_score = 0
    best_role = None

    for role in roles:
        score = 0
        for keyword in role.responses:
            if keyword in input_text:
                score += 1
        if score > best_score:
            best_score = score
            best_role = role
    
    if best_role is None:
        return "Not understood"
    
    for keyword, response in best_role.responses.items():
        if keyword in input_text:
            return response
    
    return "Still learning"


if __name__=="__main__":

    roles = []

    cs = Role("CS")
    cs.add_response("order", "or1")
    cs.add_response("payment", "pm1")
    cs.add_response("help", "hp1")
    roles.append(cs)

    ts = Role("TS")
    ts.add_response("bug", "bg1")
    ts.add_response("error", "err1")
    ts.add_response("notif", "notif1")
    roles.append(ts)

    while True:

        resp = interact(roles)
        print(resp)
        if(resp=="exit"):
            break
