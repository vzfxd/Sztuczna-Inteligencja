from keras.datasets import mnist
from sklearn.ensemble import RandomForestClassifier


(x_train, y_train), (x_test, y_test) = mnist.load_data()

x_train = x_train.reshape(-1, 28 * 28) / 255.0
x_test = x_test.reshape(-1, 28 * 28) / 255.0

num_trees = 10
max_steps = 100

trees = []
for _ in range(num_trees):
    tree = RandomForestClassifier(n_estimators=max_steps)
    trees.append(tree)

print("\n\nRozpoczęcie trenowania")
for tree in trees:
    tree.fit(x_train, y_train)
print("Trening zakończony")

print("Rozpoczęcie testowania")
accuracies = [tree.score(x_test, y_test) for tree in trees]
print("Testowanie zakończone")
accuracy = sum(accuracies) / len(accuracies)

print("Dokładność lasu decyzyjnego:", accuracy)