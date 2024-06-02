import img2pdf
import os

# 生成图像文件名列表
images = [f"D:\\Files\\Desktop\\new_10\\new ({str(i)}).jpg" for i in range(1, 57)]

# 输出 PDF 文件名
output_pdf = "D:\\Files\\Desktop\\new_10\\result.pdf"

# 确保所有图片都存在，可读
for image in images:
    if not os.path.isfile(image):
        print("File not exist: ", image)
        images.remove(image)

# 使用 img2pdf 将图片列表合并为 pdf
pdf_bytes = img2pdf.convert([open(img_path, 'rb').read() for img_path in images])

# 将生成的 pdf 写入文件中
with open(output_pdf, 'wb') as f:
    f.write(pdf_bytes)

print("Images successfully converted to PDF:", output_pdf)
