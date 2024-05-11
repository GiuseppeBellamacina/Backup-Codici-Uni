from os import system
from random import randint, choice

class Itemset:
    def __init__(self, items, support):
        self.items = items
        self.support = support
    
    def printItemset(self):
        print("{", end="")
        for item in self.items:
            print(item, end="")
            if item != self.items[-1]:
                print(", ", end="")
        print("}", end="")
        print(", support: " + str(self.support))

def printItemsets(itemsets):
    # print itemsets
    for itemset in itemsets:
        itemset.printItemset()
    print()

def orderbySupport(itemsets):
    # order by support
    for i in range(len(itemsets)):
        for j in range(i+1, len(itemsets)):
            if itemsets[i].support < itemsets[j].support:
                itemsets[i], itemsets[j] = itemsets[j], itemsets[i]

def selfjoin(itemsets):
    # selfjoin
    new_itemsets = []
    for i in range(len(itemsets)):
        for j in range(i+1, len(itemsets)):
            if itemsets[i].items[:-1] == itemsets[j].items[:-1]:
                new_itemset = Itemset(itemsets[i].items + [itemsets[j].items[-1]], 0)
                new_itemsets.append(new_itemset)
    return new_itemsets

def pruning(itemsets, min_support):
    # pruning
    pruned_itemsets = []
    for itemset in itemsets:
        if itemset.support >= min_support:
            pruned_itemsets.append(itemset)
    return pruned_itemsets

def support_count(itemsets, transactions):
    # support count
    for itemset in itemsets:
        for transaction in transactions:
            if set(itemset.items).issubset(set(transaction)):
                itemset.support += 1

def apriori(transactions, items, min_support, order_by_support=False):
    support_count(items, transactions)
    itemsets = pruning(items, min_support)
    if order_by_support:
        orderbySupport(itemsets)
    printItemsets(itemsets)
    while itemsets:
        itemsets = selfjoin(itemsets)
        support_count(itemsets, transactions)
        itemsets = pruning(itemsets, min_support)
        if order_by_support:
            orderbySupport(itemsets)
        printItemsets(itemsets)

def itemsGenerator(transactions):
    tmp = []
    for transaction in transactions:
        for item in transaction:
            if item not in tmp:
                tmp.append(item)
    tmp.sort()
    items = []
    for item in tmp:
        items.append(Itemset([item], 0))
    return items

def genTransactions(items, n_transactions, max_items_per_transaction):
    file = open("transactions.txt", "w")
    for i in range(n_transactions):
        transaction = []
        n = randint(1, max_items_per_transaction)
        while len(transaction) < n:
            item = choice(items)
            if item not in transaction:
                transaction.append(item)
            else:
                continue
        for item in transaction:
            file.write(str(item) + " ")
        file.write("\n")
    file.close()

def getTransactions():
    transactions = []
    file = open("transactions.txt", "r")
    for line in file:
        transaction = []
        for item in line.strip().split():
            transaction.append(item)
        transactions.append(transaction)
    file.close()
    return transactions

def main():
    system("cls")
    items = ["A", "B", "C", "D", "E", "F", "G", "H", "I"]
    genTransactions(items, 500000, 5)
    transactions = getTransactions()
    itemsets = itemsGenerator(transactions)
    apriori(transactions, itemsets, 500, True)
    
main()