function [  ] = feature_fullvisual( net,mapnum )  
names=net.blob_names;  
featuremap=net.blobs(names{mapnum}).get_data();%获取指定层的特征图  
[m_size,n_size,num,crop]=size(featuremap)%获取特征图大小，长*宽*卷积核个数*图片个数  
row=crop;%行数  
col=num;%列数  
feature_map=zeros(m_size*row,n_size*col);  
for i=0:row-1  
    for j=0:col-1  
        feature_map(i*m_size+1:(i+1)*m_size,j*n_size+1:(j+1)*n_size)=(mapminmax(featuremap(:,:,j+1,i+1),0,1)*255)';  
    end  
end  
figure  
imshow(uint8(feature_map))  
str=strcat('feature map num:',num2str(row*col));  
title(str)  
end 