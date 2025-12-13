# Punch-Out: Juego de Boxeo

## Descripción General

Punch-Out es un juego de boxeo en 2D desarrollado en C++ usando la librería SFML (Simple and Fast Multimedia Library). Ofrece una experiencia de combate dinámico donde el jugador se enfrenta a un oponente en emocionantes rounds de boxeo.

## Objetivos

- **Modo Solo/IA**: Derrotar al oponente controlado por inteligencia artificial acertando puños hasta reducir su salud a cero, antes de que el IA te derrote a ti.
- **Modo 2 Jugadores**: Competir contra otro jugador en partidas de boxeo estratégicas donde ambos tienen oportunidad de ganar.

## Reglas Principales

### Sistema de Salud y Derriba
- Cada boxeador comienza con 100 puntos de vida (150 en modo Solo para el IA)
- Al recibir golpes, la salud se reduce
- Cuando la salud llega a 0, el boxeador es derribado (KO - Knock Out)
- El primer boxeador en ser derribado pierde el round
- Se pueden acumular múltiples derriba para intensificar la música de combate

### Sistema de Energía
- Los boxeadores poseen energía que se regenera constantemente
- Cada golpe consume energía
- Sin suficiente energía, no puedes atacar
- Bloquear también consume energía pero reduce el daño recibido

### Música Dinámica
- La música de combate se mantiene en un estado normal al inicio
- Cuando cualquier boxeador acumula 2 derriba, la música cambia a una versión más intensa
- La música vuelve a la normalidad cuando comienza un nuevo round

## Modos de Juego

### Modo Solo (Versión Prueba)
- Juega contra una **Inteligencia Artificial**
- Los boxeadores se posicionan en el centro de la pantalla
- El movimiento está **limitado solo a dirección horizontal**
- El IA no se mueve, solo ataca o se defiende
- **Dificultad aumentada**:
  - El IA tiene 150 puntos de vida
  - El IA dispone de 130 de energía máxima
  - El IA consume menos energía por golpe (15 vs 22)
  - El IA regenera energía más rápido
- **El jugador NO puede bloquear** en este modo

### Modo 2 Jugadores
- Competencia clásica entre dos jugadores humanos
- Ambos boxeadores pueden moverse libremente por el ring
- Ambos pueden atacar y bloquear sin restricciones
- Mecánicas equilibradas para ambos contendientes

## Controles

### Ataques y Movimiento
- **W** - Saltar/Movimiento vertical (Solo modo 2 Jugadores)
- **A** - Movimiento a la izquierda
- **D** - Movimiento a la derecha
- **ESPACIO** - Atacar/Golpear
- **S** - Bloquear (Solo modo 2 Jugadores)

### Menú y Opciones
- **O** - Abrir/Cerrar menú de opciones durante el combate
- **U** - Salir del juego (desde el menú de opciones)
- **ESPACIO** - Reiniciar el juego después de un KO

### Selección de Modo
- En el menú principal, selecciona:
  - **Modo A (Blanco)**: Juega en Modo Solo contra la IA
  - **Modo B (Amarillo)**: Juega en Modo 2 Jugadores


### Sistemas del Juego
- **Motor Físico Simplificado**: Posicionamiento y colisiones básicas
- **Sistema de Inteligencia Artificial**: Máquina de estados con selección de acciones aleatoria
- **Sistema de Audio Dinámico**: Música que responde al estado del juego
- **Interfaz Gráfica**: Menús de selección, indicadores de salud, energía y derriba

### Componentes Principales
- Sistema de salud y regeneración
- Sistema de energía y consumo
- Animaciones de ataque, bloqueo, daño y KO
- Gestión de rounds y contador de victorias
- Menú de opciones en juego

## Cómo Jugar

1. **Selecciona el modo de juego** en la pantalla inicial
2. **Entrena tu estrategia**:
   - En modo Solo: Aprende los patrones del IA
   - En modo 2 Jugadores: Coordina tus acciones con tu oponente
3. **Gestiona tu energía** - No malgastes golpes
4. **Usa el bloqueo estratégicamente** - Reduce el daño pero consume energía
5. **Derriba a tu oponente** - Reduce su salud a 0 para ganar el round
6. **Gana múltiples rounds** - Acumula derriba para intensificar la acción

