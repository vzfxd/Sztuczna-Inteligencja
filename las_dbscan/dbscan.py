import numpy as np
from keras.datasets import mnist


def dbscan(X, epsilon, min_samples):
    
    labels = np.zeros(len(X))
    cluster_id = 0

    for i in range(len(X)):
        if labels[i] != 0:
            continue

        neighbors = get_neighbors(X, i, epsilon)

        if len(neighbors) < min_samples:
            labels[i] = -1
            continue

        cluster_id += 1
        labels[i] = cluster_id


        j = 0
        while j < len(neighbors):
            neighbor = neighbors[j]
            if labels[neighbor] == -1:
                labels[neighbor] = cluster_id

                new_neighbors = get_neighbors(X, neighbor, epsilon)
                if len(new_neighbors) >= min_samples:
                    neighbors += [n for n in new_neighbors if n not in neighbors]

            if labels[neighbor] == 0:
                labels[neighbor] = cluster_id

            j += 1

    return labels


def get_neighbors(X, point_index, epsilon):
    neighbors = []
    point = X[point_index]

    for i in range(len(X)):
        if i == point_index:
            continue

        neighbor = X[i]
        distance = get_distance(point, neighbor)
        
        if distance <= epsilon:
            neighbors.append(i)

    return neighbors


def get_distance(img1, img2):
    normalized_img1 = img1 / 255.0
    normalized_img2 = img2 / 255.0
    return np.linalg.norm(normalized_img1 - normalized_img2)

def accuracy_cluster_labels(labels, true_labels):
    clusters = np.unique(labels)
    correct_labels = 0
    total_labels = 0

    for cluster in clusters:
        if cluster == -1:
            continue

        cluster_indices = np.where(labels == cluster)[0]
        cluster_labels = true_labels[cluster_indices]

        # Sprawdzenie dominującej etykiety w klastrze
        unique_labels, label_counts = np.unique(cluster_labels, return_counts=True)
        dominant_label = unique_labels[np.argmax(label_counts)]

        # Porównanie etykiet w klastrze z dominującą etykietą
        correct_labels += np.sum(cluster_labels == dominant_label)
        total_labels += len(cluster_labels)

    accuracy = correct_labels / total_labels

    print(f"Skuteczność klastryzacji: {accuracy:.2%}")


(x_train, y_train), (x_test, y_test) = mnist.load_data()

X = x_test[:1000]
X = X.reshape(len(X), -1)

epsilon = 9
min_samples = 50

labels = dbscan(X, epsilon, min_samples)

n_clusters = len(set(labels)) - (1 if -1 in labels else 0)
n_noise = list(labels).count(-1)

print(f"\n\nLiczba klastrów: {n_clusters}")
print(f"Liczba punktów odstających: {n_noise}")

accuracy_cluster_labels(labels,y_test[:1000])

