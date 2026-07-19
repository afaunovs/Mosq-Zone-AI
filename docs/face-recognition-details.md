# 👤 Распознавание лиц в Mosq-Zone AI

## Обзор

Модуль распознавания лиц был разработан в рамках дипломной работы и интегрирован в систему Mosq-Zone AI.

---

## Архитектура модуля
┌─────────────────────────────────────────────────────────────┐
│ Модуль распознавания лиц │
├─────────────────────────────────────────────────────────────┤
│ │
│ ┌──────────────────────────────────────────────────────┐ │
│ │ 1. Получение кадра │ │
│ │ ZoneMinder → Извлечение кадра (every 5 sec) │ │
│ └──────────────────────┬───────────────────────────────┘ │
│ │ │
│ ▼ │
│ ┌──────────────────────────────────────────────────────┐ │
│ │ 2. Детекция лица │ │
│ │ Используется: OpenCV Haar Cascade или DNN │ │
│ └──────────────────────┬───────────────────────────────┘ │
│ │ │
│ ▼ │
│ ┌──────────────────────────────────────────────────────┐ │
│ │ 3. Извлечение признаков │ │
│ │ Нейронная сеть (FaceNet / ArcFace) │ │
│ │ Выход: 128-мерный вектор │ │
│ └──────────────────────┬───────────────────────────────┘ │
│ │ │
│ ▼ │
│ ┌──────────────────────────────────────────────────────┐ │
│ │ 4. Сравнение с базой │ │
│ │ Metric Learning (Cosine Distance) │ │
│ │ Порог: 0.6 (настраиваемый) │ │
│ └──────────────────────┬───────────────────────────────┘ │
│ │ │
│ ▼ │
│ ┌──────────────────────────────────────────────────────┐ │
│ │ 5. Результат │ │
│ │ KNOWN → "Вход разрешен" │ │
│ │ UNKNOWN → "Посторонний!" + уведомление │ │
│ └──────────────────────────────────────────────────────┘ │
└─────────────────────────────────────────────────────────────┘

text

---

## Технические детали

### Модель
- **Архитектура:** FaceNet (Inception ResNet v1)
- **Размер входного изображения:** 160x160 пикселей
- **Выход:** 128-мерный вектор эмбеддингов
- **Точность:** 95%+ на LFW (Labeled Faces in the Wild)

### База данных
- Хранится в виде: `путь_к_изображению → вектор_признаков`
- Формат: JSON или SQLite
- Обновляется через веб-интерфейс

### Производительность
| Этап | Время (на Orange Pi ZERO 3) |
|------|----------------------------|
| Детекция лица | ~0.5 сек |
| Извлечение признаков | ~1.5 сек |
| Сравнение с базой | ~0.2 сек |
| **Итого** | **~2.2 сек/кадр** |

---

## Пример кода (базовый)

```python
# face_recognition_server.py (ДЕМО-ВЕРСИЯ)
# Полная версия предоставляется по запросу

import cv2
import numpy as np
import face_recognition
import json
import paho.mqtt.client as mqtt

class FaceRecognitionSystem:
    def __init__(self, face_db_path="face_db.json"):
        self.face_db = self.load_face_db(face_db_path)
        self.known_encodings = []
        self.known_names = []
        
        # Загрузка базы
        for name, encoding in self.face_db.items():
            self.known_names.append(name)
            self.known_encodings.append(np.array(encoding))
    
    def load_face_db(self, path):
        with open(path, 'r') as f:
            return json.load(f)
    
    def detect_face(self, frame):
        # Детекция лица
        face_locations = face_recognition.face_locations(frame)
        face_encodings = face_recognition.face_encodings(frame, face_locations)
        return face_locations, face_encodings
    
    def compare_faces(self, face_encoding, tolerance=0.6):
        # Сравнение с базой
        matches = face_recognition.compare_faces(
            self.known_encodings, 
            face_encoding, 
            tolerance=tolerance
        )
        
        # Поиск ближайшего совпадения
        if True in matches:
            match_index = matches.index(True)
            return self.known_names[match_index], "KNOWN"
        else:
            return "Unknown", "UNKNOWN"

# MQTT Callback
def on_face_detected(name, status):
    client = mqtt.Client()
    client.connect("localhost", 1883)
    
    payload = json.dumps({
        "name": name,
        "status": status,
        "timestamp": datetime.now().isoformat()
    })
    client.publish("mosq-zone/face/detected", payload)
    client.disconnect()