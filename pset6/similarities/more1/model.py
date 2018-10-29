from enum import Enum

"""Types of operations"""
class Operation(Enum):
    DELETED = 1
    INSERTED = 2
    SUBSTITUTED = 3

    def __str__(self):
        return str(self.name.lower())

"""Take 2 strings, return similarity this strings and optimal way go from first to second"""
def distance(a,b):
    # Create the cost matrix
    cost = [[(0,None) for j in range(len(b)+1)]for i in range(len(a)+1)]

    # Start value
    for i in range(1, len(a)+1):
        cost[i][0]=(i,Operation.DELETED)
    for j in range(1, len(b)+1):
        cost[0][j]=(j,Operation.INSERTED)

    # Fill the matrix using recursion
    for i in range(1,len(a)+1):
        for j in range(1,len(b)+1):
            deletion_cost = cost[i-1][j][0]+1
            insertion_cost = cost[i][j-1][0] +1
            if a[i-1]==b[j-1]:
                substitution_cost = cost[i-1][j-1][0]
            else:
                substitution_cost = cost[i-1][j-1][0]+1

            if substitution_cost<=insertion_cost and substitution_cost<=deletion_cost:
                cost[i][j] = (substitution_cost,Operation.SUBSTITUTED)
            elif deletion_cost<=insertion_cost and deletion_cost <=substitution_cost:
                cost[i][j] = (deletion_cost,Operation.DELETED)
            else:
                cost[i][j] = (insertion_cost,Operation.INSERTED)
    return cost
