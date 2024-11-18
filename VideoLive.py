import serial
import base64
import cv2
import numpy as np

SERIAL_PORT = "COM3"
BAUD_RATE = 115200

def main():
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print("Aguardando dados da ESP32-CAM...")
    
    buffer = ""
    
    while True:
        try:
            if ser.in_waiting > 0:
                line = ser.readline().decode("utf-8").strip()
                if line == "Success":
                    try:
                        image_data = base64.b64decode(buffer)
                        nparr = np.frombuffer(image_data, np.uint8)
                        frame = cv2.imdecode(nparr, cv2.IMREAD_COLOR)
                        if frame is not None:
                            cv2.imshow("ESP32-CAM - Video ao Vivo", frame)
                        if cv2.waitKey(1) & 0xFF == ord('q'):
                            break
                    except Exception as e:
                        print(f"Erro ao processar a imagem: {e}")
                    buffer = ""
                else:
                    buffer += line
        except KeyboardInterrupt:
            print("\nEncerrando...")
            break

    ser.close()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
