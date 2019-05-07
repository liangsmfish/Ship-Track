# Ship-Track
Linux + OpenCV<br>
  原圖<br>
  ![img](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_1.jpg)
  1.利用 OPENCV 內建 knn 函式建立背景模型<br>
  2.利用 GaussianBlur 前處理並轉灰階影像<br>  
  ![img2](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_2.jpg)
  
  3.先做 Sobel 處理找邊<br>
  ![img3](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_3.jpg)
  
  4.經過 MedianBlur 模糊處理大部分太細微的背景<br>
  ![img4](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_4.jpg)
  
  5.再經過經過形態學(Closing)的處理 erode(3x3) -> dilate(7x7) <br>
  ![img5](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_5.jpg)
    
  6.Threshold = 40，超過 40 轉 255<br>
  ![img6](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_6.jpg)
  
  7.最後修正 MedianBlur + dilate(9x9)<br>
  ![img7](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_7.jpg)
  
  8.DrawContours 畫出輪廓<br>
  ![img8](https://github.com/liangsmfish/Ship-Track/blob/master/img/231_8.jpg)
