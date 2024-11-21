import tkinter as tk
import requests

ESP8266_URL = "http://192.168.0.126"

roda_girando = False

def alternar_roda():
    global roda_girando
    try:
        if roda_girando:
            requests.get(f"{ESP8266_URL}/LOW")
            print("Roda desativada.")
            botao.config(text="Ligar motor", bg="#4CAF50", fg="white")
        else:
            requests.get(f"{ESP8266_URL}/HIGH")
            print("Roda ativada.")
            botao.config(text="Desligar motor", bg="#F44336", fg="white")
        roda_girando = not roda_girando
    except requests.exceptions.RequestException as e:
        print(f"Erro ao enviar comando: {e}")

janela = tk.Tk()
janela.title("Ideia que me salvou")
janela.geometry("400x200")
janela.configure(bg="#282C34")

titulo = tk.Label(janela, text="Último recurso", font=("Arial", 18, "bold"), bg="#282C34", fg="white")
titulo.pack(pady=10)

botao = tk.Button(janela, text="Ligar motor", font=("Arial", 16), bg="#4CAF50", fg="white", command=alternar_roda)
botao.pack(pady=20, ipadx=20, ipady=10)

rodape = tk.Label(janela, text="Conexão via WiFi, não funciona com WPA3", font=("Arial", 10), bg="#282C34", fg="white")
rodape.pack(side="bottom", pady=10)

janela.mainloop()
