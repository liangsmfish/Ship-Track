# Ship-Track
Linux + OpenCV<br>
  1.利用 OPENCV 內建 knn 函式建立背景模型<br>
  [img]: https://github.com/liangsmfish/Ship-Track/blob/master/231_2.jpg
  2.利用 GaussianBlur 前處理並轉灰階影像<br>  
  3.先做 Sobel 處理找邊<br>
  4.經過 MedianBlur 模糊處理大部分太細微的背景<br>
  5.再經過經過形態學(Closing)的處理 erode(3x3) -> dilate(7x7) <br>
  6.Threshold = 40，超過 40 轉 255<br>
  7.最後修正 MedianBlur + dilate(9x9)<br>
  8.DrawContours 畫出輪廓<br>
