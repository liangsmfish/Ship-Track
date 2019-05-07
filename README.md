# Ship-Track
Linux + OpenCV
  1.利用 OPENCV 內建 knn 函式建立背景模型
  2.利用 GaussianBlur 前處理並轉灰階影像
  3.先做 Sobel 處理找邊
  4.經過 MedianBlur 模糊處理大部分太細微的背景
  5.再經過經過形態學(Closing)的處理 erode(3x3) -> dilate(7x7) 
  6.Threshold = 40，超過 40 轉 255
  7.最後修正 MedianBlur + dilate(9x9)
  8.DrawContours 畫出輪廓
