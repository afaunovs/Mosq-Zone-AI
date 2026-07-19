# 🚀 Инструкция по установке Mosq-Zone AI

## Предварительные требования

### Оборудование
- [x] ESP32-CAM модуль (AI Thinker)
- [x] Orange Pi ZERO 3 (или Raspberry Pi 3B+)
- [x] MicroSD карта (32GB+)
- [x] ssd (128GB+) с платой подключения по usb
- [x] Блок питания 5В 2А
- [x] Wi-Fi роутер

### Программное обеспечение
- [x] Arduino IDE (для прошивки ESP32)
- [x] Linux (Debian12 / Armbian) на Orange Pi
---

## Шаг 1: Подготовка Orange Pi

### 1.1 Установка ОС
bash
# Загрузите образ Armbian для Orange Pi ZERO 3
# Запишите на SD карту с помощью BalenaEtcher/Rufus
# Вставьте SD карту и включите устройство
Подключение к SSH
bash
ssh orangepi@<IP_адрес>
# Пароль по умолчанию: orangepi
устанвливаем оболочку и сразу же переносим систему на ssd, а sd-карту оставляем как есть он будет только запускать загрузчик Grub и потом переходит на ssd для полноценной работы системы

### 1.2 полная инструкция по установке и настройке zoneminder
установка и настрока zoneminder на debian 12 -bookworm/armbian
сначала загружаем репозитории и обновляем пакеты

sudo apt update -y
sudo apt upgrade -y

дальше устанавливаем необходимые программы, фалы и зависимости

sudo apt install apache2 mariadb-server php php-mysql php-gd php-xml php-cli ffmpeg vlc build-essential mariadb-client php-zip php-mbstring php-common libapache2-mod-php

установка zoneminder

sudo apt install zoneminder

далле добваляем часовой пояс и изменяем настройки php в файле:

sudo nano /etc/php/8.2/apache2/php.ini

находим и заменяем

max_execution_time = 300
max_input_time = 300
memory_limit = 256M
post_max_size = 32M
upload_max_filesize = 16M
date.timezone = "Europe/Moscow" - или же другой timezone (свой)
сохраняем и выходим

после запускаем настройку mysql командой:

sudo mysql_secure_installation

Нажмите Enter, чтобы войти в систему под учетной записью root
Введите Y и нажмите Enter, чтобы установить пароль root, введите пароль дважды для подтверждения
Введите Y и нажмите Enter, чтобы удалить анонимных пользователей
Введите Y и нажмите Enter, чтобы запретить удаленный вход в систему под учетной записью root
Введите Y и нажмите Enter, чтобы удалить тестовую базу данных
Введите Y и нажмите Enter, чтобы перезагрузить таблицы привилегий

создаем базу данных zoneminder  в  MySQL ( при это также будут созданы пользователь zoneminder  по умолчанию и его права доступа в MySQL).
пр появлении запроса ввелите пароль root-пользователя сервера/базы данных
после перезапускаем его

sudo mysql -uroot -p < /usr/share/zoneminder/db/zm_create.sql

sudo mysql -uroot -p -e "grant all on zm.* to 'zmuser'@localhost identified by 'zmpass';"

sudo mysqladmin -uroot -p reload

устанавливаем права и разрешения

sudo chmod 640 /etc/zm/zm.conf

sudo chown root:www-data /etc/zm/zm.conf

sudo chown -R www-data:www-data /var/cache/zoneminder/

sudo chmod 755 /var/cache/zoneminder/

сохраняем файл конфигурации в случии если будем иди будет изменен

sudo cp /etc/apache2/conf-available/zoneminder.conf /etc/apache2/conf-available/zoneminder.conf.sav

добавляем нового пользователя в группу video

sudo adduser www-data video

включаем автозапуск службы zoneminder

sudo systemctl enable zoneminder

запускаем zoneminder

sudo systemctl start zoneminder
или
sudo systemctl restart zoneminder

включаем конфигурацию zoneminder в apache2

sudo a2enconf zoneminder
sudo a2enmod rewrite
sudo a2enmod headers
sudo a2enmod expires
sudo a2enmod cgi
и перезагружаем службу apache2
sudo service apache2 reload

Откройте веб-браузер и перейдите по ссылке http://DNSorIP/zm
Выберите, следует ли предоставлять разработчикам доступ к данным об использовании> нажмите Применить
Нажмите Параметры в верхней панели навигации
Выберите Пользователей в левом меню навигации
Нажмите на ссылку администратор * имя пользователя
Введите безопасный пароль в поля "Новый пароль" и "Подтвердить пароль" и нажмите "Сохранить"
Чтобы добавить камеру, нажмите Консоль в верхней панели навигации, а затем нажмите кнопку Добавить и заполните форму
### Добавление камеры
Зайдите в веб-интерфейс ZoneMinder: http://<IP>:8080/zm

Нажмите Add New Monitor

Настройки:

General → Name: ESP32-CAM-1

Source → Source Type: Remote

Source → Remote Host Name: 192.168.1.XXX (IP ESP32)

Source → Remote Host Port: 80

Source → Remote Path: /stream

Нажмите Save

Настройка MQTT в ZoneMinder
В ZoneMinder → Options → MQTT

Включите MQTT

Укажите брокер: localhost:1883

Сохраните

######
#### 📝 Примечание
Полный код ESP32-CAM, модуль распознавания лиц и конфигурации доступны по запросу через контакты в README.