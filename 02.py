from SetOperations import Set

n1 = int(input("Enter number of elements in set 1: "))
s1 = Set(n1)
print("Set 1: ", s1)


while(True):
    print("\n----- SET OPERATIONS MENU -----")
    print("1. Add element to set\n2. Remove element from set\n3. Display elements in set")
    print("4. Search element in set\n5. Display size of set")
    print("6. Intersection of two sets\n7. Union of two sets")
    print("8. Difference between two sets\n9. Check subset")
    print("10. Exit")

    ch = int(input("Enter your choice(1-9): "))

    if(ch == 1):
        elem_add = int(input("Enter element to be added: "))
        s1.add(elem_add)
    
    elif(ch == 2):
        elem_del = int(input("Enter element to be deleted: "))
        s1.remove(elem_del)

    elif(ch == 3):
        print("Set 1: ", s1)

    elif(ch == 4):
        elem_search = int(input("Enter element to search: "))
        result = s1.__contains__(elem_search)
        if(result):
            print("Element found in set")
        else:
            print("Element not found in set")

    elif(ch == 5):
        size = s1.__len__()
        print("Size of set: ", size)
    
    elif(ch == 6):
        n2 = int(input("To find intersection, enter number elements in second set: "))
        s2 = Set(n2)
        print("set 2: ", s2)
        inter = s1.intersection(s2)
        print("Intersection: ", inter)

    elif(ch == 7):
        n2 = int(input("To find union, enter number elements in second set: "))
        s2 = Set(n2)
        print("set 2: ", s2)
        union = s1.union(s2)
        print("Union: ", union)

    elif(ch == 8):
        n2 = int(input("To find difference, enter number elements in second set: "))
        s2 = Set(n2)
        print("set 2: ", s2)
        diff = s1.difference(s2)
        print("Difference between set 1 and set 2: ", diff)

    elif(ch == 9):
        n2 = int(input("To check subset, enter number elements in second set: "))
        s2 = Set(n2)
        print("set 2: ", s2)
        result = s1.isSubsetOf(s2)
        if(result):
            print("Set 2 is subset of Set 1")
        else:
            print("Set 2 is not a subset of Set 1")
    
    elif(ch == 10):
        print("***** You have exited *****")
        break

    else:
        print("Please enter valid choice")