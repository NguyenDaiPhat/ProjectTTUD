import csv
import matplotlib.pyplot as plt

def draw(csv_file, ax):
    x = []
    y = []
    with open(csv_file, 'r') as file:
        reader = csv.reader(file)
        for row in reader:
            x.append(float(row[0]))
            y.append(float(row[1]))

    # Vẽ biểu đồ trong ô ax
    ax.plot(x, y)
    ax.scatter(x, y, color='red', label='Các điểm')
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_title('Biểu đồ đường đi')
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
plt.subplots_adjust(wspace=0.4)

# Hiển thị ma trận biểu đồ
plt.show()