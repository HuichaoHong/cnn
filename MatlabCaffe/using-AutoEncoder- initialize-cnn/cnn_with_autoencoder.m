%%
%Author:honghuichao
%%
addpath('D:/caffe') %加入+caffe路径  
caffe.set_mode_gpu();%设置CPU模式  
model = 'D:/caffe/models/bvlc_reference_caffenet/deploy_copy.prototxt';%模型  
net=caffe.Net(model,'test');%测试  
%net.copy_from(weights);
%[blob_w,blob_b]=AutoEncoder('C:\\Users\\Administrator\\Desktop\\pic2\\1\\',8,48);
net.params('conv1', 1).set_data(blob_w);
net.params('conv1', 2).set_data(blob_b); 

