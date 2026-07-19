// ========== HTML СТРАНИЦА (в точности как у вас, но с WebSocket на порту 81) ==========
const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CAM Security System</title>
    <style>
        .container_1 {
            position: relative;
            width: 100%;
            max-width: 1280px;
        }
        .container_1 img {
            width: 100%;
            height: auto;
        }
        .container_1 .btn_up {
            position: absolute;
            top: 2%;
            left: 50%;
            transform: translate(-50%, -50%);
            background-color: rgb(9,9,9,0);
            color: rgb(0,0,0,0);
            font-size: 16px;
            width: 60px;
            height: 60px;
            border-top: 10px solid #d000ff;
            border-right: 10px solid #d000ff;
            border-bottom: 0px solid #d000ff;
            border-left: 0px solid #d000ff;
            cursor: pointer;
            border-radius: 5px;
            transform: rotate(-45deg);
        }
        .container_1 .btn_left {
            position: absolute;
            top: 48%;
            left: 2%;
            transform: translate(-50%, -50%);
            background-color: rgb(9,9,9,0);
            color: rgb(0,0,0,0);
            font-size: 16px;
            width: 60px;
            height: 60px;
            border-top: 10px solid #d000ff;
            border-right: 10px solid #d000ff;
            border-bottom: 0px solid #d000ff;
            border-left: 0px solid #d000ff;
            cursor: pointer;
            border-radius: 5px;
            transform: rotate(-135deg);
        }
        .container_1 .btn_right {
            position: absolute;
            top: 48%;
            left: 94%;
            transform: translate(-50%, -50%);
            background-color: rgb(9,9,9,0);
            color: rgb(0,0,0,0);
            font-size: 16px;
            width: 60px;
            height: 60px;
            border-top: 10px solid #d000ff;
            border-right: 10px solid #d000ff;
            border-bottom: 0px solid #d000ff;
            border-left: 0px solid #d000ff;
            cursor: pointer;
            border-radius: 5px;
            transform: rotate(45deg);
        }
        .container_1 .btn_down {
            position: absolute;
            top: 94%;
            left: 50%;
            transform: translate(-50%, -50%);
            background-color: rgb(9,9,9,0);
            color: rgb(0,0,0,0);
            font-size: 16px;
            width: 60px;
            height: 60px;
            border-top: 10px solid #d000ff;
            border-right: 10px solid #d000ff;
            border-bottom: 0px solid #d000ff;
            border-left: 0px solid #d000ff;
            cursor: pointer;
            border-radius: 5px;
            transform: rotate(135deg);
        }
        .container_1 .btn:hover {
            background-color: black;
            color: white;
        }
        .serv_position {
            position: absolute;
            top: 7%;
            left: 5%;
            transform: translate(-50%, -50%);
            background-color: rgb(9,9,9,0);
            color: #d000ff;
            font-size: 16px;
            font-family: fantasy;
            width: 200px;
            height: 100px;
            border: none;
            cursor: pointer;
            border-radius: 5px;
            text-align: center;
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="container_1">
            <img id="stream_photo" src="" alt="Camera Stream">
            <button class="btn_up" id="btn_up">""</button>
            <button class="btn_left" id="btn_left">""</button>
            <button class="btn_right" id="btn_right">""</button>
            <button class="btn_down" id="btn_down">""</button>
            <span class="serv_position" id="serv_position">Servo_position</span>
        </div>
        <div class="controls">
            <div class="input-group">
                <label>Шаг поворота вверх/вниз (угол наклона):</label>
                <input type="number" id="step_updown" placeholder="5" value="5" min="0" max="180" step="1" class="number-input">
            </div>
            <div class="input-group">
                <label>Шаг поворота влево/вправо (угол поворота):</label>
                <input type="number" id="step_leftright" placeholder="5" value="5" min="0" max="180" step="1" class="number-input">
            </div>
            <div class="info-text">
                ⚡ По умолчанию шаг поворота равен 5. Измените значение в полях выше, и новый шаг автоматически применится к кнопкам.
                <br>📌 Текущий угол сервопривода отображается в левом верхнем углу.
            </div>
            <div class="ai-status" style="margin: 20px; padding: 15px; background: #1e1e2f; border-radius: 10px; color: #0f0; font-family: monospace;">
                <strong>🤖 AI DETECTION:</strong> <span id="aiResult">Waiting...</span>
            </div>
        </div>
    </div>
    </body>
</html>
)=====";