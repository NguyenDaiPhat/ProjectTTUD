import csv
import matplotlib.pyplot as plt

def draw(csv_file, ax):
    with open('input/input1.csv', 'r') as file:
        reader = csv.reader(file)
        next(reader)
        order_index = 1

        for row in reader:
            x1, y1, x2, y2, label = map(float, row)
            ax.scatter(x1, y1, color='red', label='Pick up', s=10)
            ax.scatter(x2, y2, color='blue', label='Delivery', s=10)
            ax.text(x1, y1, f'(P{order_index})', ha='right', va='bottom', fontsize=8)
            ax.text(x2, y2, f'(D{order_index})', ha='left', va='bottom', fontsize=8)
            order_index += 1
    x = []
    y = []
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            x.append(float(row[0]))
            y.append(float(row[1]))

    # Vẽ biểu đồ trong ô ax
    ax.plot(x, y)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title(csv_file)
    ax.grid(True, linestyle='--', alpha=0.5)

    # Vẽ mũi tên trên các đường đi
    arrowprops = dict(arrowstyle='->')
    for i in range(1, len(x)):
        ax.annotate('', xy=(x[i], y[i]), xytext=(x[i-1], y[i-1]), arrowprops=arrowprops)

# Tạo figure và các axes trong ma trận 1x2
fig, axs = plt.subplots(1, 2, figsize=(10, 4))

# Đường dẫn tới hai file dữ liệu tương tự nhau
csv_file1 = 'output/outputGen.csv'
csv_file2 = 'output/outputOp.csv'

# Vẽ biểu đồ từ file dữ liệu 1 trong ô đầu tiên
draw(csv_file1, axs[0])

# Vẽ biểu đồ từ file dữ liệu 2 trong ô thứ hai
draw(csv_file2, axs[1])

# Tùy chỉnh khoảng cách giữa các ô trong ma trận
plt.subplots_adjust(wspace=0.2)

# Hiển thị ma trận biểu đồ
plt.show()