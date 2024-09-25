# APPYL (Aparato para pisar y leer)

Este proyecto fue creado para facilitar la lectura de partituras en una tablet, permitiendo pasar de página simplemente pisando un pedal con el pie. Es una herramienta útil para músicos que necesitan cambiar páginas sin utilizar las manos, optimizando su desempeño en presentaciones en vivo o ensayos.

## Inspiración

Creo firmemente en la colaboración y el código abierto. Mi intención al compartir este proyecto es permitir que cualquier persona interesada pueda construir su propio pedal de cambio de página para partituras, de manera libre y accesible. Al liberar este código, espero que más personas puedan personalizarlo, mejorarlo y adaptarlo a sus necesidades, contribuyendo así al espíritu de comunidad y libre acceso al conocimiento.

> "El código abierto nos une y nos permite construir juntos un futuro mejor."

## Clases Principales

### 1. `Footswitch`
Esta clase gestiona el comportamiento del pedal de pie. Se encarga de leer el estado de los pulsadores conectados al ESP32 y traducir esas acciones en comandos para cambiar la página en la tablet. Además, soporta la funcionalidad de "modo inverso", en la cual se cambia el comportamiento del pedal después de una acción prolongada.

- **Funciones destacadas**:
  - `getStatus()`: Retorna el estado actual de los pulsadores.
  - `executeAction()`: Realiza la acción asignada al pulsador según el estado actual.

### 2. `KeyMap`
Define la configuración del mapeo de teclas para el Bluetooth, permitiendo que el ESP32 actúe como un teclado que envía los comandos correctos a la tablet.

- **Funciones destacadas**:
  - `getAction(key)`: Retorna la acción asignada a una tecla específica.

### 3. `LedManager`
Maneja los LEDs conectados al ESP32. Estos LEDs pueden usarse para mostrar el estado del dispositivo, indicando si está activo o si está en modo configuración.

- **Funciones destacadas**:
  - `hit(pin, duration)`: Enciende un LED en el pin especificado por un tiempo determinado.
  - `titilar(pin, interval)`: Hace titilar el LED en el pin especificado a intervalos regulares.

### 4. `Preference_Manager`
Esta clase se encarga de guardar y recuperar las preferencias del dispositivo, como las acciones asociadas a los pulsadores y el estado del modo inverso. Utiliza el sistema de almacenamiento interno del ESP32.

- **Funciones destacadas**:
  - `getPreference(key)`: Obtiene el valor de una preferencia guardada.
  - `setPreference(key, value)`: Guarda una preferencia.

### 5. `WebPortal`
Esta clase proporciona una interfaz web para configurar el pedal. Los usuarios pueden conectarse al ESP32 a través de Wi-Fi y cambiar las preferencias del dispositivo de manera sencilla.

- **Funciones destacadas**:
  - `begin()`: Inicia el portal web.
  - `handleClient()`: Maneja las solicitudes de los clientes conectados.

## Cómo usar este proyecto

1. Clona el repositorio en tu máquina local.
2. Configura el ESP32 con las conexiones apropiadas para los pulsadores, LEDs y la interfaz Bluetooth.
3. Sube el código al ESP32 utilizando la herramienta de Arduino o PlatformIO.
4. Conecta tu ESP32 a la tablet mediante Bluetooth y comienza a usar el pedal para pasar las páginas.

## Requisitos

- ESP32
- Pulsadores y LEDs
- Tablet con capacidad Bluetooth
- Conexiones eléctricas básicas

## To Do

- **Convertir Footswitch a template**: Adaptar la clase `Footswitch` para que funcione como un template, permitiendo implementar distintos tipos de comportamiento o hardware, por ejemplo, una versión con botones de tipo footswitch en lugar de pulsadores.
- **Tratar botones y LEDs como array**: Refactorizar el código para manejar los botones y LEDs como arreglos, facilitando la creación de dispositivos con más o menos cantidad de botones y LEDs sin cambios significativos en el código base.
- **Permitir ajustar brillo o apagar las luces desde la configuración**: Quizás pueda con alguna combinación de teclas y handlearlo desde Footswitch? veremos.
  
## Known Issues

- **LED 2 parpadea una sola vez al cambiar de modo**: Al cambiar entre modos, el LED 2 debería parpadear repetidamente, pero actualmente solo parpadea una vez. Este comportamiento inesperado aún no ha sido resuelto.

## Impresión 3d
  - Pueden ver el proyecto en thingiverse: https://www.thingiverse.com/thing:6778400

## Contribuciones

Las contribuciones son bienvenidas. Siéntete libre de hacer un fork de este proyecto, enviar un pull request o abrir issues para cualquier mejora o problema que encuentres.
