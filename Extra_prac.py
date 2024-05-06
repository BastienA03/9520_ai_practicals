from collections import deque

def print_move(source, target, disk):
    print(f"Move disk {disk} from {source} to {target}")

def hanoi(n, source, target, auxiliary):
   
    queue = deque([(source, target, auxiliary)])

    while queue:
        source, target, auxiliary = queue.popleft()

       
        if len(target) == n:
            return source, target, auxiliary

      
        if source and (not auxiliary or source[-1] < auxiliary[-1]): 
            print_move('source', 'auxiliary', source[-1])
            new_source, new_auxiliary = source[:-1], auxiliary + [source[-1]]
            queue.append((new_source, target, new_auxiliary))

      
        if source and (not target or source[-1] < target[-1]):
            print_move('source', 'target', source[-1])
            new_source, new_target = source[:-1], target + [source[-1]]
            queue.append((new_source, new_target, auxiliary))

     
        if auxiliary and (not target or auxiliary[-1] < target[-1]):
            print_move('auxiliary', 'target', auxiliary[-1])
            new_auxiliary, new_target = auxiliary[:-1], target + [auxiliary[-1]]
            queue.append((source, new_target, new_auxiliary))

source = [3, 2, 1]
target = []
auxiliary = []
hanoi(3, source, target, auxiliary)







output
Move disk 1 from source to auxiliary
Move disk 1 from source to target
Move disk 2 from source to target
Move disk 1 from auxiliary to target
Move disk 2 from source to auxiliary
Move disk 1 from auxiliary to target
Move disk 2 from source to auxiliary
Move disk 3 from source to auxiliary


