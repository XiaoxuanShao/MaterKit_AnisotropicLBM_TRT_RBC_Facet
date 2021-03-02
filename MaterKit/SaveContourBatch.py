from paraview.simple import * 
paraview.simple._DisableFirstRenderCameraReset()

import os
workspace = "J:\data"
os.chdir(workspace)   #修改当前工作目录
os.getcwd()      #获取当前工作目录
print("The workspace \n"+workspace+"\nis changed!")
#print("The workspace is NOT changed!\n")

subfolder = "\csv"
#########################################################
####以下为创建目录的函数mkdir()
def mkdir(path):
    # 引入模块
    import os
    # 去除首位空格
    path=path.strip()
    # 去除尾部 \ 符号
    path=path.rstrip("\\")
    # 判断路径是否存在
    # 存在     True
    # 不存在   False
    isExists=os.path.exists(path)
    # 判断结果
    if not isExists:
        # 如果不存在则创建目录, 创建目录操作函数
        os.makedirs(path)
        print 'The path\n' + path + '\nis created.'
        return True
    else:
        # 如果目录存在则不创建，并提示目录已存在
        print 'The path\n' + path + '\nexists.'
        return False
# 定义要创建的目录
mkpath=workspace + subfolder
# 调用函数
mkdir(mkpath)
#print(mkpath)
#########################################################
fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t0.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops0.csv', proxy = contour1, Precision=8)
print("Loops = 0/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops500.csv', proxy = contour1, Precision=8)
print("Loops = 500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t1000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops1000.csv', proxy = contour1, Precision=8)
print("Loops = 1000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t1500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops1500.csv', proxy = contour1, Precision=8)
print("Loops = 1500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t2000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops2000.csv', proxy = contour1, Precision=8)
print("Loops = 2000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t2500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops2500.csv', proxy = contour1, Precision=8)
print("Loops = 2500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t3000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops3000.csv', proxy = contour1, Precision=8)
print("Loops = 3000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t3500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops3500.csv', proxy = contour1, Precision=8)
print("Loops = 3500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t4000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops4000.csv', proxy = contour1, Precision=8)
print("Loops = 4000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t4500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops4500.csv', proxy = contour1, Precision=8)
print("Loops = 4500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t5000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops5000.csv', proxy = contour1, Precision=8)
print("Loops = 5000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t5500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops5500.csv', proxy = contour1, Precision=8)
print("Loops = 5500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t6000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops6000.csv', proxy = contour1, Precision=8)
print("Loops = 6000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t6500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops6500.csv', proxy = contour1, Precision=8)
print("Loops = 6500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t7000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops7000.csv', proxy = contour1, Precision=8)
print("Loops = 7000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t7500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops7500.csv', proxy = contour1, Precision=8)
print("Loops = 7500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t8000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops8000.csv', proxy = contour1, Precision=8)
print("Loops = 8000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t8500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops8500.csv', proxy = contour1, Precision=8)
print("Loops = 8500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t9000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops9000.csv', proxy = contour1, Precision=8)
print("Loops = 9000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t9500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops9500.csv', proxy = contour1, Precision=8)
print("Loops = 9500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t10000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops10000.csv', proxy = contour1, Precision=8)
print("Loops = 10000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t10500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops10500.csv', proxy = contour1, Precision=8)
print("Loops = 10500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t11000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops11000.csv', proxy = contour1, Precision=8)
print("Loops = 11000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t11500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops11500.csv', proxy = contour1, Precision=8)
print("Loops = 11500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t12000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops12000.csv', proxy = contour1, Precision=8)
print("Loops = 12000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t12500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops12500.csv', proxy = contour1, Precision=8)
print("Loops = 12500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t13000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops13000.csv', proxy = contour1, Precision=8)
print("Loops = 13000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t13500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops13500.csv', proxy = contour1, Precision=8)
print("Loops = 13500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t14000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops14000.csv', proxy = contour1, Precision=8)
print("Loops = 14000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t14500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops14500.csv', proxy = contour1, Precision=8)
print("Loops = 14500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t15000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops15000.csv', proxy = contour1, Precision=8)
print("Loops = 15000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t15500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops15500.csv', proxy = contour1, Precision=8)
print("Loops = 15500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t16000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops16000.csv', proxy = contour1, Precision=8)
print("Loops = 16000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t16500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops16500.csv', proxy = contour1, Precision=8)
print("Loops = 16500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t17000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops17000.csv', proxy = contour1, Precision=8)
print("Loops = 17000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t17500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops17500.csv', proxy = contour1, Precision=8)
print("Loops = 17500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t18000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops18000.csv', proxy = contour1, Precision=8)
print("Loops = 18000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t18500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops18500.csv', proxy = contour1, Precision=8)
print("Loops = 18500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t19000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops19000.csv', proxy = contour1, Precision=8)
print("Loops = 19000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t19500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops19500.csv', proxy = contour1, Precision=8)
print("Loops = 19500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t20000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops20000.csv', proxy = contour1, Precision=8)
print("Loops = 20000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t20500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops20500.csv', proxy = contour1, Precision=8)
print("Loops = 20500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t21000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops21000.csv', proxy = contour1, Precision=8)
print("Loops = 21000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t21500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops21500.csv', proxy = contour1, Precision=8)
print("Loops = 21500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t22000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops22000.csv', proxy = contour1, Precision=8)
print("Loops = 22000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t22500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops22500.csv', proxy = contour1, Precision=8)
print("Loops = 22500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t23000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops23000.csv', proxy = contour1, Precision=8)
print("Loops = 23000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t23500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops23500.csv', proxy = contour1, Precision=8)
print("Loops = 23500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t24000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops24000.csv', proxy = contour1, Precision=8)
print("Loops = 24000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t24500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops24500.csv', proxy = contour1, Precision=8)
print("Loops = 24500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t25000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops25000.csv', proxy = contour1, Precision=8)
print("Loops = 25000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t25500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops25500.csv', proxy = contour1, Precision=8)
print("Loops = 25500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t26000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops26000.csv', proxy = contour1, Precision=8)
print("Loops = 26000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t26500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops26500.csv', proxy = contour1, Precision=8)
print("Loops = 26500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t27000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops27000.csv', proxy = contour1, Precision=8)
print("Loops = 27000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t27500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops27500.csv', proxy = contour1, Precision=8)
print("Loops = 27500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t28000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops28000.csv', proxy = contour1, Precision=8)
print("Loops = 28000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t28500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops28500.csv', proxy = contour1, Precision=8)
print("Loops = 28500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t29000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops29000.csv', proxy = contour1, Precision=8)
print("Loops = 29000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t29500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops29500.csv', proxy = contour1, Precision=8)
print("Loops = 29500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t30000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops30000.csv', proxy = contour1, Precision=8)
print("Loops = 30000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t30500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops30500.csv', proxy = contour1, Precision=8)
print("Loops = 30500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t31000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops31000.csv', proxy = contour1, Precision=8)
print("Loops = 31000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t31500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops31500.csv', proxy = contour1, Precision=8)
print("Loops = 31500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t32000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops32000.csv', proxy = contour1, Precision=8)
print("Loops = 32000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t32500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops32500.csv', proxy = contour1, Precision=8)
print("Loops = 32500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t33000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops33000.csv', proxy = contour1, Precision=8)
print("Loops = 33000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t33500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops33500.csv', proxy = contour1, Precision=8)
print("Loops = 33500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t34000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops34000.csv', proxy = contour1, Precision=8)
print("Loops = 34000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t34500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops34500.csv', proxy = contour1, Precision=8)
print("Loops = 34500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t35000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops35000.csv', proxy = contour1, Precision=8)
print("Loops = 35000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t35500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops35500.csv', proxy = contour1, Precision=8)
print("Loops = 35500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t36000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops36000.csv', proxy = contour1, Precision=8)
print("Loops = 36000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t36500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops36500.csv', proxy = contour1, Precision=8)
print("Loops = 36500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t37000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops37000.csv', proxy = contour1, Precision=8)
print("Loops = 37000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t37500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops37500.csv', proxy = contour1, Precision=8)
print("Loops = 37500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t38000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops38000.csv', proxy = contour1, Precision=8)
print("Loops = 38000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t38500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops38500.csv', proxy = contour1, Precision=8)
print("Loops = 38500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t39000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops39000.csv', proxy = contour1, Precision=8)
print("Loops = 39000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t39500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops39500.csv', proxy = contour1, Precision=8)
print("Loops = 39500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t40000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops40000.csv', proxy = contour1, Precision=8)
print("Loops = 40000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t40500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops40500.csv', proxy = contour1, Precision=8)
print("Loops = 40500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t41000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops41000.csv', proxy = contour1, Precision=8)
print("Loops = 41000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t41500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops41500.csv', proxy = contour1, Precision=8)
print("Loops = 41500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t42000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops42000.csv', proxy = contour1, Precision=8)
print("Loops = 42000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t42500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops42500.csv', proxy = contour1, Precision=8)
print("Loops = 42500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t43000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops43000.csv', proxy = contour1, Precision=8)
print("Loops = 43000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t43500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops43500.csv', proxy = contour1, Precision=8)
print("Loops = 43500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t44000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops44000.csv', proxy = contour1, Precision=8)
print("Loops = 44000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t44500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops44500.csv', proxy = contour1, Precision=8)
print("Loops = 44500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t45000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops45000.csv', proxy = contour1, Precision=8)
print("Loops = 45000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t45500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops45500.csv', proxy = contour1, Precision=8)
print("Loops = 45500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t46000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops46000.csv', proxy = contour1, Precision=8)
print("Loops = 46000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t46500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops46500.csv', proxy = contour1, Precision=8)
print("Loops = 46500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t47000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops47000.csv', proxy = contour1, Precision=8)
print("Loops = 47000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t47500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops47500.csv', proxy = contour1, Precision=8)
print("Loops = 47500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t48000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops48000.csv', proxy = contour1, Precision=8)
print("Loops = 48000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t48500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops48500.csv', proxy = contour1, Precision=8)
print("Loops = 48500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t49000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops49000.csv', proxy = contour1, Precision=8)
print("Loops = 49000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t49500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops49500.csv', proxy = contour1, Precision=8)
print("Loops = 49500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t50000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops50000.csv', proxy = contour1, Precision=8)
print("Loops = 50000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t50500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops50500.csv', proxy = contour1, Precision=8)
print("Loops = 50500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t51000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops51000.csv', proxy = contour1, Precision=8)
print("Loops = 51000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t51500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops51500.csv', proxy = contour1, Precision=8)
print("Loops = 51500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t52000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops52000.csv', proxy = contour1, Precision=8)
print("Loops = 52000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t52500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops52500.csv', proxy = contour1, Precision=8)
print("Loops = 52500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t53000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops53000.csv', proxy = contour1, Precision=8)
print("Loops = 53000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t53500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops53500.csv', proxy = contour1, Precision=8)
print("Loops = 53500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t54000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops54000.csv', proxy = contour1, Precision=8)
print("Loops = 54000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t54500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops54500.csv', proxy = contour1, Precision=8)
print("Loops = 54500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t55000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops55000.csv', proxy = contour1, Precision=8)
print("Loops = 55000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t55500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops55500.csv', proxy = contour1, Precision=8)
print("Loops = 55500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t56000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops56000.csv', proxy = contour1, Precision=8)
print("Loops = 56000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t56500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops56500.csv', proxy = contour1, Precision=8)
print("Loops = 56500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t57000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops57000.csv', proxy = contour1, Precision=8)
print("Loops = 57000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t57500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops57500.csv', proxy = contour1, Precision=8)
print("Loops = 57500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t58000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops58000.csv', proxy = contour1, Precision=8)
print("Loops = 58000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t58500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops58500.csv', proxy = contour1, Precision=8)
print("Loops = 58500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t59000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops59000.csv', proxy = contour1, Precision=8)
print("Loops = 59000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t59500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops59500.csv', proxy = contour1, Precision=8)
print("Loops = 59500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t60000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops60000.csv', proxy = contour1, Precision=8)
print("Loops = 60000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t60500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops60500.csv', proxy = contour1, Precision=8)
print("Loops = 60500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t61000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops61000.csv', proxy = contour1, Precision=8)
print("Loops = 61000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t61500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops61500.csv', proxy = contour1, Precision=8)
print("Loops = 61500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t62000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops62000.csv', proxy = contour1, Precision=8)
print("Loops = 62000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t62500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops62500.csv', proxy = contour1, Precision=8)
print("Loops = 62500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t63000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops63000.csv', proxy = contour1, Precision=8)
print("Loops = 63000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t63500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops63500.csv', proxy = contour1, Precision=8)
print("Loops = 63500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t64000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops64000.csv', proxy = contour1, Precision=8)
print("Loops = 64000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t64500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops64500.csv', proxy = contour1, Precision=8)
print("Loops = 64500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t65000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops65000.csv', proxy = contour1, Precision=8)
print("Loops = 65000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t65500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops65500.csv', proxy = contour1, Precision=8)
print("Loops = 65500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t66000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops66000.csv', proxy = contour1, Precision=8)
print("Loops = 66000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t66500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops66500.csv', proxy = contour1, Precision=8)
print("Loops = 66500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t67000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops67000.csv', proxy = contour1, Precision=8)
print("Loops = 67000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t67500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops67500.csv', proxy = contour1, Precision=8)
print("Loops = 67500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t68000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops68000.csv', proxy = contour1, Precision=8)
print("Loops = 68000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t68500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops68500.csv', proxy = contour1, Precision=8)
print("Loops = 68500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t69000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops69000.csv', proxy = contour1, Precision=8)
print("Loops = 69000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t69500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops69500.csv', proxy = contour1, Precision=8)
print("Loops = 69500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t70000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops70000.csv', proxy = contour1, Precision=8)
print("Loops = 70000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t70500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops70500.csv', proxy = contour1, Precision=8)
print("Loops = 70500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t71000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops71000.csv', proxy = contour1, Precision=8)
print("Loops = 71000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t71500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops71500.csv', proxy = contour1, Precision=8)
print("Loops = 71500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t72000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops72000.csv', proxy = contour1, Precision=8)
print("Loops = 72000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t72500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops72500.csv', proxy = contour1, Precision=8)
print("Loops = 72500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t73000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops73000.csv', proxy = contour1, Precision=8)
print("Loops = 73000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t73500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops73500.csv', proxy = contour1, Precision=8)
print("Loops = 73500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t74000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops74000.csv', proxy = contour1, Precision=8)
print("Loops = 74000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t74500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops74500.csv', proxy = contour1, Precision=8)
print("Loops = 74500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t75000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops75000.csv', proxy = contour1, Precision=8)
print("Loops = 75000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t75500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops75500.csv', proxy = contour1, Precision=8)
print("Loops = 75500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t76000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops76000.csv', proxy = contour1, Precision=8)
print("Loops = 76000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t76500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops76500.csv', proxy = contour1, Precision=8)
print("Loops = 76500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t77000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops77000.csv', proxy = contour1, Precision=8)
print("Loops = 77000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t77500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops77500.csv', proxy = contour1, Precision=8)
print("Loops = 77500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t78000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops78000.csv', proxy = contour1, Precision=8)
print("Loops = 78000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t78500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops78500.csv', proxy = contour1, Precision=8)
print("Loops = 78500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t79000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops79000.csv', proxy = contour1, Precision=8)
print("Loops = 79000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t79500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops79500.csv', proxy = contour1, Precision=8)
print("Loops = 79500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t80000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops80000.csv', proxy = contour1, Precision=8)
print("Loops = 80000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t80500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops80500.csv', proxy = contour1, Precision=8)
print("Loops = 80500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t81000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops81000.csv', proxy = contour1, Precision=8)
print("Loops = 81000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t81500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops81500.csv', proxy = contour1, Precision=8)
print("Loops = 81500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t82000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops82000.csv', proxy = contour1, Precision=8)
print("Loops = 82000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t82500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops82500.csv', proxy = contour1, Precision=8)
print("Loops = 82500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t83000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops83000.csv', proxy = contour1, Precision=8)
print("Loops = 83000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t83500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops83500.csv', proxy = contour1, Precision=8)
print("Loops = 83500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t84000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops84000.csv', proxy = contour1, Precision=8)
print("Loops = 84000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t84500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops84500.csv', proxy = contour1, Precision=8)
print("Loops = 84500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t85000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops85000.csv', proxy = contour1, Precision=8)
print("Loops = 85000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t85500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops85500.csv', proxy = contour1, Precision=8)
print("Loops = 85500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t86000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops86000.csv', proxy = contour1, Precision=8)
print("Loops = 86000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t86500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops86500.csv', proxy = contour1, Precision=8)
print("Loops = 86500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t87000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops87000.csv', proxy = contour1, Precision=8)
print("Loops = 87000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t87500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops87500.csv', proxy = contour1, Precision=8)
print("Loops = 87500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t88000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops88000.csv', proxy = contour1, Precision=8)
print("Loops = 88000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t88500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops88500.csv', proxy = contour1, Precision=8)
print("Loops = 88500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t89000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops89000.csv', proxy = contour1, Precision=8)
print("Loops = 89000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t89500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops89500.csv', proxy = contour1, Precision=8)
print("Loops = 89500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t90000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops90000.csv', proxy = contour1, Precision=8)
print("Loops = 90000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t90500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops90500.csv', proxy = contour1, Precision=8)
print("Loops = 90500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t91000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops91000.csv', proxy = contour1, Precision=8)
print("Loops = 91000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t91500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops91500.csv', proxy = contour1, Precision=8)
print("Loops = 91500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t92000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops92000.csv', proxy = contour1, Precision=8)
print("Loops = 92000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t92500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops92500.csv', proxy = contour1, Precision=8)
print("Loops = 92500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t93000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops93000.csv', proxy = contour1, Precision=8)
print("Loops = 93000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t93500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops93500.csv', proxy = contour1, Precision=8)
print("Loops = 93500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t94000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops94000.csv', proxy = contour1, Precision=8)
print("Loops = 94000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t94500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops94500.csv', proxy = contour1, Precision=8)
print("Loops = 94500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t95000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops95000.csv', proxy = contour1, Precision=8)
print("Loops = 95000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t95500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops95500.csv', proxy = contour1, Precision=8)
print("Loops = 95500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t96000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops96000.csv', proxy = contour1, Precision=8)
print("Loops = 96000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t96500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops96500.csv', proxy = contour1, Precision=8)
print("Loops = 96500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t97000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops97000.csv', proxy = contour1, Precision=8)
print("Loops = 97000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t97500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops97500.csv', proxy = contour1, Precision=8)
print("Loops = 97500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t98000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops98000.csv', proxy = contour1, Precision=8)
print("Loops = 98000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t98500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops98500.csv', proxy = contour1, Precision=8)
print("Loops = 98500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t99000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops99000.csv', proxy = contour1, Precision=8)
print("Loops = 99000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t99500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops99500.csv', proxy = contour1, Precision=8)
print("Loops = 99500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t100000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops100000.csv', proxy = contour1, Precision=8)
print("Loops = 100000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t100500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops100500.csv', proxy = contour1, Precision=8)
print("Loops = 100500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t101000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops101000.csv', proxy = contour1, Precision=8)
print("Loops = 101000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t101500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops101500.csv', proxy = contour1, Precision=8)
print("Loops = 101500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t102000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops102000.csv', proxy = contour1, Precision=8)
print("Loops = 102000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t102500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops102500.csv', proxy = contour1, Precision=8)
print("Loops = 102500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t103000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops103000.csv', proxy = contour1, Precision=8)
print("Loops = 103000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t103500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops103500.csv', proxy = contour1, Precision=8)
print("Loops = 103500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t104000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops104000.csv', proxy = contour1, Precision=8)
print("Loops = 104000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t104500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops104500.csv', proxy = contour1, Precision=8)
print("Loops = 104500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t105000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops105000.csv', proxy = contour1, Precision=8)
print("Loops = 105000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t105500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops105500.csv', proxy = contour1, Precision=8)
print("Loops = 105500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t106000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops106000.csv', proxy = contour1, Precision=8)
print("Loops = 106000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t106500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops106500.csv', proxy = contour1, Precision=8)
print("Loops = 106500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t107000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops107000.csv', proxy = contour1, Precision=8)
print("Loops = 107000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t107500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops107500.csv', proxy = contour1, Precision=8)
print("Loops = 107500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t108000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops108000.csv', proxy = contour1, Precision=8)
print("Loops = 108000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t108500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops108500.csv', proxy = contour1, Precision=8)
print("Loops = 108500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t109000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops109000.csv', proxy = contour1, Precision=8)
print("Loops = 109000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t109500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops109500.csv', proxy = contour1, Precision=8)
print("Loops = 109500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t110000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops110000.csv', proxy = contour1, Precision=8)
print("Loops = 110000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t110500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops110500.csv', proxy = contour1, Precision=8)
print("Loops = 110500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t111000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops111000.csv', proxy = contour1, Precision=8)
print("Loops = 111000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t111500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops111500.csv', proxy = contour1, Precision=8)
print("Loops = 111500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t112000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops112000.csv', proxy = contour1, Precision=8)
print("Loops = 112000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t112500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops112500.csv', proxy = contour1, Precision=8)
print("Loops = 112500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t113000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops113000.csv', proxy = contour1, Precision=8)
print("Loops = 113000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t113500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops113500.csv', proxy = contour1, Precision=8)
print("Loops = 113500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t114000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops114000.csv', proxy = contour1, Precision=8)
print("Loops = 114000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t114500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops114500.csv', proxy = contour1, Precision=8)
print("Loops = 114500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t115000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops115000.csv', proxy = contour1, Precision=8)
print("Loops = 115000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t115500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops115500.csv', proxy = contour1, Precision=8)
print("Loops = 115500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t116000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops116000.csv', proxy = contour1, Precision=8)
print("Loops = 116000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t116500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops116500.csv', proxy = contour1, Precision=8)
print("Loops = 116500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t117000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops117000.csv', proxy = contour1, Precision=8)
print("Loops = 117000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t117500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops117500.csv', proxy = contour1, Precision=8)
print("Loops = 117500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t118000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops118000.csv', proxy = contour1, Precision=8)
print("Loops = 118000/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t118500.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops118500.csv', proxy = contour1, Precision=8)
print("Loops = 118500/119000")


fluid_t = LegacyVTKReader(FileNames=['./vtk/fluid_t119000.vtk'])
# create a new 'Contour'
contour1 = Contour(Input=fluid_t)
# Properties modified on contour1
contour1.ContourBy = ['POINTS', 'order_parameter']
contour1.Isosurfaces = [0.0]
contour1.PointMergeMethod = 'Uniform Binning'
SaveData('./csv/loops119000.csv', proxy = contour1, Precision=8)
print("Loops = 119000/119000")



