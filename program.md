

# 一、open3d

格式转换

```python
bin_data = np.fromfile(bin_path,dtype=np.float32)
bin_data = bin_data.reshape(-1,4)
bin_data = bin_data[:,:-1]
print(bin_data.shape)
pcd = o3d.geometry.PointCloud()
####将numpy数据转换为open3d格式open3d.cpu.pybind.geometry.PointCloud#####
pcd.points = o3d.open3d.utility.Vector3dVector(bin_data)
# 创建窗口对象
vis = o3d.visualization.Visualizer()
#设置窗口标题
vis.create_window(window_name="kitti")
#设置点云大小
vis.get_render_option().point_size = 1
#设置颜色背景为黑色
opt = vis.get_render_option()
opt.background_color = np.asarray([0, 0, 0])
voxel_size = 0.1
downpcd = pcd.voxel_down_sample(voxel_size)
copy = np.asarray(downpcd.points)
print(copy.shape)
####################
#设置点的颜色为白色
pcd.paint_uniform_color([1,1,1])
#将点云加入到窗口中
vis.add_geometry(pcd)
vis.run()
vis.destroy_window()
```

# 二、矩阵运算

1. `*`和`@`

   ```python
   # * 代表点乘
   import numpy as np
   mat1 = np.array([[1,2,3,],[4,5,6]])
   print(mat1)
   mat2 = np.ones([2,3])*2
   res1 = mat1 * mat2
   print(res1)
   # @ 代表矩阵乘法 等同于 np.dot
   mat3 = np.ones([3,2])
   print(mat3)
   res2 = mat1 @ mat3
   print(res2)
   res3 = np.dot(mat1,mat3)
   print(res3)
   ```

   

2. 待定

# 三、numpy

1. `np.meshgrid()`

   ```python
   numpy.meshgrid(*xi, **kwargs)
   '''
   indexing = 'xy' (default)
   index = 'ij'
   作用：使用meshgrid方法，你只需要构造一个表示x轴上的坐标的向量和一个表示y轴上的坐标的向量;然后作为参数给到meshgrid(),该函数就会返回相应维度的两个矩阵
   '''
   # index = 'xy'
   x = np.array([0, 0.5, 1])
   y = np.array([0,1])
   
   xv,yv = np.meshgrid(x, y)
   print("xv的维度:{},shape:{}".format(xv.ndim, xv.shape))
   print("yv的维度:{},shape:{}".format(yv.ndim, yv.shape))
   print(xv)
   print(yv)
   
   plt.plot(xv, yv, 'o--')
   plt.grid(True)
   plt.show()
   # index = 'ij'
   x = np.array([0, 0.5, 1])
   y = np.array([0,1])
   
   xv,yv = np.meshgrid(x, y,indexing='ij')
   print("xv的维度:{},shape:{}".format(xv.ndim, xv.shape))
   print("yv的维度:{},shape:{}".format(yv.ndim, yv.shape))
   print(xv)
   print(yv)
   
   plt.plot(xv, yv, 'o--')
   plt.grid(True)
   plt.show()
   ```

2. `np.newaxis`

   配合切片使用使用，作用就是在这一位置增加一个一维，这一位置指的是np.newaxis所在的位置

   ```python
   x1 = np.array([1, 2, 3, 4, 5])
   # the shape of x1 is (5,)
   x1_new = x1[:, np.newaxis] #(5,1)
   # array([[1],
   #        [2],
   #        [3],
   #        [4],
   #        [5]])
   x1_new = x1[np.newaxis,:] 
   # now, the shape of x1_new is (1, 5)
   # array([[1, 2, 3, 4, 5]])
   
   ```

3. `np.title()`

   ```python
   # np.tile(A,reps)
   '''
   1. reps=（2轴，1轴，0轴）
   2. array([[[0,1,2]]])，中括号从左向右依次表示：2轴，1轴，0轴 
   3. reps中每轴上的数字是几，就将array中对应轴(中括号)中数据
   '''
   a = np.array([0, 1, 2])
   t_a = np.tile(a, (2, 2))
   b = np.array([[1, 2], [3, 4]])
   t_b = np.tile(b, (2, 1))
   ```

4. IOU计算

   ```python
   def iou_jit(boxes, query_boxes, eps=0.0):
       """calculate box iou. note that jit version runs 2x faster than cython in
       my machine!
       Parameters
       ----------
       boxes: (N, 4) ndarray of float,(N,4(xmin,ymin,xmax,ymax))
       query_boxes: (K, 4) ndarray of float
       Returns
       -------
       overlaps: (N, K) ndarray of overlap between boxes and query_boxes
       """
       N = boxes.shape[0]
       K = query_boxes.shape[0]
       overlaps = np.zeros((N, K), dtype=boxes.dtype)
       for k in range(K):
           box_area = ((query_boxes[k, 2] - query_boxes[k, 0] + eps) *
                       (query_boxes[k, 3] - query_boxes[k, 1] + eps))
           for n in range(N):
               iw = (min(boxes[n, 2], query_boxes[k, 2]) -
                     max(boxes[n, 0], query_boxes[k, 0]) + eps)
               if iw > 0:
                   ih = (min(boxes[n, 3], query_boxes[k, 3]) -
                         max(boxes[n, 1], query_boxes[k, 1]) + eps)
                   if ih > 0:
                       ua = (
                           (boxes[n, 2] - boxes[n, 0] + eps) *
                           (boxes[n, 3] - boxes[n, 1] + eps) + box_area - iw * ih)
                       overlaps[n, k] = iw * ih / ua
       return overlaps
   ```

5. `np.where`

   ```python
   #用法一
   #当self.net_input(X)返回的值大于等于0.0时，where返回1，否则返回0
   input = np.array([[1,1,1,1],[2,2,2,2],[3,3,3,3],[4,4,4,4]])
   print(input)
   res = np.where(input >= 2, 1, 0)
   print(res)
   #用法二，获取目标值的索引
   idx = np.where(input == 4)
   print(idx) #(array([3, 3, 3, 3], dtype=int64), array([0, 1, 2, 3], dtype=int64))
   ```

6. `np.unique`

   ```python
   # a, s,p = np.unique(A, return_index=True, return_inverse=True)
   # 去除重复元素返回数组
   # return_index=True表示返回新列表元素在旧列表中的位置，并以列表形式储存在s中
   # return_inverse=True 表示返回旧列表元素在新列表中的位置，并以列表形式储存在p中
   # axis: int,如果指定了axis，则以该维索引构成的子数组作为元素，将整个数组视为一维数组进行处理
   A = [1, 2, 2, 5,3, 4, 3]
   A = [[3, 4, 5],[3,4,5],[5,6,7]]
   a, s,p = np.unique(A, return_index=True, return_inverse=True)
   print(a)
   print(s)
   print(p)
   # 运行结果
   # [1 2 3 4 5]
   # [0 1 4 5 3]
   # [0 1 1 4 2 3 2]
   ```

7. cuda bug

   无进程号显存被占用

   ```bash
   fuser -v /dev/nvidia*
   import os
   os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID" #（保证程序cuda序号与实际cuda序号对应）
   os.environ['CUDA_VISIBLE_DEVICES'] = "1"  #（代表仅使用第0，1号GPU）
   ```

   

8. 待定

# 四、MMCV学习

读取config配置文件

```python
# config_a.py
a = 1
b = dict(b1=[0, 1, 2], b2=None)
# config_b.py
_base_ = './config_a.py'
b = dict(b2=1)
c = (1, 2)
#####
config = Config.fromfile("./config_b.py")
print(config)
# Output
# Config (path: ./config_b.py): {'a': 1, 'b': {'b1': [0, 1, 2], 'b2': 1}, 'c': (1, 2)}
当子配置文件和父配置文件存在key冲突的时候,会以子配置文件为主
```

注册机制

```python
#conver.py
from build import CONVERTERS
@CONVERTERS.register_module()
class Converter1(object):
    def __init__(self, a, b):
        self.a = a
        self.b = b
    def pr(self):
        print("a= {},b={}".format(self.a,self.b))
#build.py
from mmcv.utils import Registry
CONVERTERS = Registry("converter")
#main.py
from build import CONVERTERS
from con import Converter1
if __name__ == "__main__":
    converter_cfg = dict(type='Converter1', a=1, b=2)
    converter = CONVERTERS.build(converter_cfg)  # 这里的build是mmcv帮我们默认实现了
    converter.pr()
    print(converter)
```

# 五、python class

1. 类的继承

   ```python
   # super(A,self).__init()执行父类的构造函数，能够调用父类的属性
   #测试一，简单继承无法继承属性
   '''
   class Root(object):
       def __init__(self):
           self.x= '这是属性'
   
       def fun(self):
           print(self.x)
           print('这是方法')
           
   class A(Root):
       def __init__(self):
           print('实例化时执行')
   '''
   #测试二，父类方法使用父类属性时，子类继承时也不能用父类的属性
   '''
   class Root(object):
       def __init__(self):
           self.x= '这是属性'
   
       def fun(self):
           # print(self.x)
           print('这是方法')
           
   class A(Root):
       def __init__(self):
           print('实例化时执行')
   '''
   ```

2. `@classmethod`和`@staticmethod`

   ```python
   #@classmethod
   class Data_test2(object):
       day=0
       month=0
       year=0
       def __init__(self,year=0,month=0,day=0):
           self.day=day
           self.month=month
           self.year=year
       @classmethod
       def get_date(cls,data_as_string):
    
           #这里第一个参数是cls， 表示调用当前的类名
    
           year,month,day=map(int,data_as_string.split('-'))
           date1=cls(year,month,day)     #返回的是一个初始化后的类
           return date1
    
       def out_date(self):
           print("year :",self.year)
           print("month :",self.month)
           print("day :",self.day)
   #@staticmethod 静态方法，对于类共有的属性，分别使用类名调用和使用实例调用静态方法
   class Pizza(object):
       def __init__(self, radius, height):
           self.radius = radius
           self.height = height
    
       @staticmethod
       def compute_area(radius):
           return math.pi * (radius ** 2)
    
       @classmethod
       def compute_volume(cls, height, radius):
           return height * cls.compute_area(radius)    #调用@staticmethod方法
    
       def get_volume(self):
           return self.compute_volume(self.height, self.radius)
   if __name__=='__main__':
       # r=Data_test2.get_date("2020-1-1")
       # r.out_date()
       r = Pizza.compute_area(4)
       print(r)
   ```

   ​    

3. 待定

# 六、pytorch训练

```python
import os
os.environ["CUDA_DEVICE_ORDER"] = "PCI_BUS_ID"  #（保证程序cuda序号与实际cuda序号对应）
os.environ['CUDA_VISIBLE_DEVICES'] = "0"  #（代表仅使用第0，1号GPU）
```





