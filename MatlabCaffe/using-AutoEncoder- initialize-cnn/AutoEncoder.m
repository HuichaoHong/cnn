function [blob_w,blob_b]=AutoEncoder(file_path,kernel_size,kernel_num)
%%
%Author：honghuichao
%data：2017-06-16
%function：
%%
%input:
%kernel_size=8;
%kernel_num=48;
%file_path='C:\\Users\\Administrator\\Desktop\\pic2\\0\\';

%output:
%blob_w
%blob_b
%%
files = dir(fullfile(strcat(file_path,'*.bmp')));
length_files = length(files);
block=[];
for i = 1:length_files;%%% 第i块图像
    img = imread(strcat(file_path,files(i).name));%%%%读入文件夹
    img=rgb2gray(img);%%%把图像灰度化
    [w,h]=size(img);
    for j=1:h-kernel_size-1%%图像位置索引
        for k=1:w-kernel_size-1
            %将图像转为一维向量
            temp=img(j:j+kernel_size-1,k:(k-1)+kernel_size);
            temp_1d=reshape(temp,1,kernel_size*kernel_size);
        end
         block(:,i*j)=temp_1d;
    end
end
bpnet=newff(block,block,kernel_num,{'logsig', 'logsig'}, 'traingdx', 'learngdm');
net.trainParam.epochs=1000;%允许最大训练步数2000步
net.trainParam.goal=0.001; %训练目标最小误差0.001
net.trainParam.show=10; %每间隔100步显示一次训练结果
net.trainParam.lr=0.05; %学习速率0.05
bpnet=train(bpnet,block, block);
w=cell2mat(bpnet.iw(1,1))%%%%查看权值
b=cell2mat(bpnet.b(1))
%%%%%%%filter
filter=[];
blob_w=[]
blob_b=[]
for i=1:size(w,1);
    kernel=reshape(w(i,:),kernel_size,kernel_size)
    blob_w(:,:,1,i)=kernel(:,:);
    blob_b(i,1)=b(i);
    imshow(kernel);
    name=['kernel',num2str(i),'.jpg'];
    %imwrite(kernel,name)
end
%%
