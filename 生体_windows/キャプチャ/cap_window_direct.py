import dxcam
import cv2

camera = dxcam.create(output_color="BGR")
frame = camera.grab()  # 全画面キャプチャ
cv2.imshow("Screen", frame)
cv2.waitKey(0)
cv2.destroyAllWindows()
