#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include "classic_boxer.hpp"
#include "hitman_boxer.hpp"

using namespace sf;
using namespace std;

int main()
{
	Texture texturaRing;
	if (!texturaRing.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/ring top down.png"))
	{
		return -1;
	}

	Vector2u dimensionesRing = texturaRing.getSize();
	const float escalaRing = 2.125f;
	Vector2u dimensionesVentana(static_cast<unsigned int>(dimensionesRing.x * escalaRing),
		static_cast<unsigned int>(dimensionesRing.y * escalaRing));
	RenderWindow ventanaRing(VideoMode(dimensionesVentana.x, dimensionesVentana.y), "Boxing", Style::Close);

	Sprite lienzoRing(texturaRing);
	lienzoRing.setScale(escalaRing, escalaRing);

	Music musicaIntro;
	if (!musicaIntro.openFromFile("assets/musica/Intro.ogg"))
	{
		return -1;
	}
	musicaIntro.setLoop(true);
	musicaIntro.play();

	Music musicaCombate;
	if (!musicaCombate.openFromFile("assets/musica/Musica Combate.ogg"))
	{
		return -1;
	}
	musicaCombate.setLoop(true);

	Music musicaCombate2;
	if (!musicaCombate2.openFromFile("assets/musica/Musica Combate 2.ogg"))
	{
		return -1;
	}
	musicaCombate2.setLoop(true);

	// Pantalla de menú principal
	bool pantallaMenuActiva = true;
	bool mostrarInstrucciones = false;
	bool pantallaInstruccionesActiva = false;
	Clock relojParpadeoInstrucciones;

	// Control de alternancia de canciones de combate basado en derribos
	bool musicaIntensaActiva = false;  // true cuando algún jugador está a punto de KO (2 derribos)

	SoundBuffer bufferGolpe;
	if (!bufferGolpe.loadFromFile("assets/sonidos/golpe 2.wav"))
	{
		return -1;
	}
	Sound sonidoGolpe;
	sonidoGolpe.setBuffer(bufferGolpe);

	SoundBuffer bufferKoFinal;
	if (!bufferKoFinal.loadFromFile("assets/sonidos/KO.wav"))
	{
		return -1;
	}
	Sound sonidoKoFinal;
	sonidoKoFinal.setBuffer(bufferKoFinal);

	SoundBuffer bufferCampana;
	if (!bufferCampana.loadFromFile("assets/sonidos/Campana.wav"))
	{
		return -1;
	}
	Sound sonidoCampana;
	sonidoCampana.setBuffer(bufferCampana);

	Texture texturaEnergiaClasicoProgreso;
	if (!texturaEnergiaClasicoProgreso.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/energy progress.png"))
	{
		return -1;
	}

	Texture texturaEnergiaClasicoDescargada;
	if (!texturaEnergiaClasicoDescargada.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/energy under.png"))
	{
		return -1;
	}

	Texture texturaEnergiaHitmanProgreso;
	if (!texturaEnergiaHitmanProgreso.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/energy progress.png"))
	{
		return -1;
	}

	Texture texturaEnergiaHitmanDescargada;
	if (!texturaEnergiaHitmanDescargada.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/energy under.png"))
	{
		return -1;
	}

	Texture texturaVidaClasicoProgreso;
	if (!texturaVidaClasicoProgreso.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/life progress.png"))
	{
		return -1;
	}

	Texture texturaVidaClasicoDescargada;
	if (!texturaVidaClasicoDescargada.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/life under.png"))
	{
		return -1;
	}

	Texture texturaVidaHitmanProgreso;
	if (!texturaVidaHitmanProgreso.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/life progress.png"))
	{
		return -1;
	}

	Texture texturaVidaHitmanDescargada;
	if (!texturaVidaHitmanDescargada.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/life under.png"))
	{
		return -1;
	}

	Texture texturaEscudoClasicoProgreso;
	if (!texturaEscudoClasicoProgreso.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/shield progress.png"))
	{
		return -1;
	}

	Texture texturaEscudoClasicoDescargado;
	if (!texturaEscudoClasicoDescargado.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/shield under.png"))
	{
		return -1;
	}

	Texture texturaEscudoHitmanProgreso;
	if (!texturaEscudoHitmanProgreso.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/shield progress.png"))
	{
		return -1;
	}

	Texture texturaEscudoHitmanDescargado;
	if (!texturaEscudoHitmanDescargado.loadFromFile("assets/Pixel Art Hitman Stance Boxer Character - v1.1/extras/shield under.png"))
	{
		return -1;
	}

	Texture texturaCorazonLleno;
	if (!texturaCorazonLleno.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/life progress.png"))
	{
		return -1;
	}

	Texture texturaCorazonVacio;
	if (!texturaCorazonVacio.loadFromFile("assets/Pixel Art Boxer Character Pack/extras/life under.png"))
	{
		return -1;
	}

	Sprite barraEnergiaClasicoProgreso(texturaEnergiaClasicoProgreso);
	Sprite barraEnergiaClasicoDescargada(texturaEnergiaClasicoDescargada);
	Sprite barraEnergiaHitmanProgreso(texturaEnergiaHitmanProgreso);
	Sprite barraEnergiaHitmanDescargada(texturaEnergiaHitmanDescargada);
	Sprite barraVidaClasicoProgreso(texturaVidaClasicoProgreso);
	Sprite barraVidaClasicoDescargada(texturaVidaClasicoDescargada);
	Sprite barraVidaHitmanProgreso(texturaVidaHitmanProgreso);
	Sprite barraVidaHitmanDescargada(texturaVidaHitmanDescargada);
	Sprite barraEscudoClasicoProgreso(texturaEscudoClasicoProgreso);
	Sprite barraEscudoClasicoDescargado(texturaEscudoClasicoDescargado);
	Sprite barraEscudoHitmanProgreso(texturaEscudoHitmanProgreso);
	Sprite barraEscudoHitmanDescargado(texturaEscudoHitmanDescargado);
	Sprite corazonRojoLleno(texturaCorazonLleno);
	Sprite corazonRojoVacio(texturaCorazonVacio);
	Sprite corazonAzulLleno(texturaCorazonLleno);
	Sprite corazonAzulVacio(texturaCorazonVacio);

	const float escalaBarraEnergiaClasico = 3.0f;
	const float escalaBarraEnergiaHitman = 3.0f;
	const float escalaBarraVidaClasico = 3.0f;
	const float escalaBarraVidaHitman = 3.0f;
	const float escalaBarraEscudoClasico = 3.0f;
	const float escalaBarraEscudoHitman = 3.0f;
	const float separacionIndicadores = 36.0f;
	const float offsetIndicadoresSuperior = 260.0f;
	const float offsetIndicadoresInferior = 25.0f;

	barraEnergiaClasicoProgreso.setScale(escalaBarraEnergiaClasico, escalaBarraEnergiaClasico);
	barraEnergiaClasicoDescargada.setScale(escalaBarraEnergiaClasico, escalaBarraEnergiaClasico);
	barraEnergiaHitmanProgreso.setScale(escalaBarraEnergiaHitman, escalaBarraEnergiaHitman);
	barraEnergiaHitmanDescargada.setScale(escalaBarraEnergiaHitman, escalaBarraEnergiaHitman);
	barraVidaClasicoProgreso.setScale(escalaBarraVidaClasico, escalaBarraVidaClasico);
	barraVidaClasicoDescargada.setScale(escalaBarraVidaClasico, escalaBarraVidaClasico);
	barraVidaHitmanProgreso.setScale(escalaBarraVidaHitman, escalaBarraVidaHitman);
	barraVidaHitmanDescargada.setScale(escalaBarraVidaHitman, escalaBarraVidaHitman);
	barraEscudoClasicoProgreso.setScale(escalaBarraEscudoClasico, escalaBarraEscudoClasico);
	barraEscudoClasicoDescargado.setScale(escalaBarraEscudoClasico, escalaBarraEscudoClasico);
	barraEscudoHitmanProgreso.setScale(escalaBarraEscudoHitman, escalaBarraEscudoHitman);
	barraEscudoHitmanDescargado.setScale(escalaBarraEscudoHitman, escalaBarraEscudoHitman);
	const float escalaCorazon = 2.6f;
	corazonRojoLleno.setScale(escalaCorazon, escalaCorazon);
	corazonRojoVacio.setScale(escalaCorazon, escalaCorazon);
	corazonAzulLleno.setScale(escalaCorazon, escalaCorazon);
	corazonAzulVacio.setScale(escalaCorazon, escalaCorazon);

	Font fuenteJuego;
	if (!fuenteJuego.loadFromFile("assets/fonts/letra/Jumps Winter.ttf"))
	{
		return -1;
	}

	Text tituloJuego;
	tituloJuego.setFont(fuenteJuego);
	tituloJuego.setString("BOXING");
	tituloJuego.setCharacterSize(128);
	tituloJuego.setFillColor(Color::White);
	const FloatRect limitesTitulo = tituloJuego.getLocalBounds();
	tituloJuego.setOrigin(limitesTitulo.left + (limitesTitulo.width * 0.5f), limitesTitulo.top + (limitesTitulo.height * 0.5f));
	tituloJuego.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.38f);

	Text textoContinuar;
	textoContinuar.setFont(fuenteJuego);
	textoContinuar.setString("Presiona SPACE para iniciar");
	textoContinuar.setCharacterSize(36);
	textoContinuar.setFillColor(Color::White);
	const FloatRect limitesContinuar = textoContinuar.getLocalBounds();
	textoContinuar.setOrigin(limitesContinuar.left + (limitesContinuar.width * 0.5f), limitesContinuar.top + (limitesContinuar.height * 0.5f));
	textoContinuar.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.6f);

	ClassicBoxer boxeadorClasico;
	if (!boxeadorClasico.load())
	{
		return -1;
	}

	HitmanBoxer boxeadorHitman;
	if (!boxeadorHitman.load())
	{
		return -1;
	}

	AnimationClip* animacionReposo = boxeadorClasico.clip("idle");
	AnimationClip* animacionPruebaJab = boxeadorClasico.clip("jab");
	AnimationClip* hitmanReposo = boxeadorHitman.clip("idle");
	if (animacionReposo == nullptr || animacionPruebaJab == nullptr || hitmanReposo == nullptr)
	{
		return -1;
	}
	const float escalaBoxeador = 4.0f;
	const float escalaHitman = 4.0f;
	const Vector2f posicionBoxeadorInicial(static_cast<float>(dimensionesVentana.x) * 0.5f,
		static_cast<float>(dimensionesVentana.y) * 0.78f);
	const Vector2f posicionHitmanInicial(static_cast<float>(dimensionesVentana.x) * 0.7f,
		static_cast<float>(dimensionesVentana.y) * 0.78f);
	Vector2f posicionBoxeador = posicionBoxeadorInicial;
	Vector2f posicionHitman = posicionHitmanInicial;
	vector<string> comboGolpes = { "body-hook", "cross", "hook", "overhand", "uppercut" };
	std::size_t indiceGolpe = 0;
	AnimationClip animacionJabReposo;
	if (!animacionJabReposo.load("assets/Pixel Art Boxer Character Pack/character/Separate Animations/jab.png", 2))
	{
		return -1;
	}
	vector<string> comboGolpesHitman = { "flicker-jab1", "flicker-jab2", "hook", "overhand", "uppercut" };
	std::size_t indiceGolpeHitman = 0;
	bool jabReposoVisible = false;
	float temporizadorJabReposo = 0.0f;
	const float duracionReposoExtendida = 2.6f;
	const float duracionJabBreve = 0.55f;
	const float energiaMaximaClasico = 120.0f;
	const float energiaMaximaHitman = 90.0f;
	float energiaClasico = energiaMaximaClasico;
	float energiaHitman = energiaMaximaHitman;
	const float costoGolpeClasico = 18.0f;
	const float costoGolpeHitman = 22.0f;
	const float regeneracionEnergiaClasico = 12.5f;
	const float regeneracionEnergiaHitman = 11.0f;

	const float vidaMaximaClasico = 80.0f;
	const float vidaMaximaHitman = 100.0f;
	float vidaClasico = vidaMaximaClasico;
	float vidaHitman = vidaMaximaHitman;
	const float golpesParaDerrotaClasico = 8.0f;
	const float golpesParaDerrotaHitman = 10.0f;
	const float danoGolpeRecibidoClasico = vidaMaximaClasico / golpesParaDerrotaClasico;
	const float danoGolpeRecibidoHitman = vidaMaximaHitman / golpesParaDerrotaHitman;

	const float escudoMaximo = 5.0f;
	float escudoClasico = escudoMaximo;
	float escudoHitman = escudoMaximo;
	const float regenEscudoPorSegundo = 0.8f;
	bool escudoClasicoActivo = false;
	bool escudoHitmanActivo = false;
	int vidasClasico = 3;
	int vidasHitman = 3;
	int numeroRound = 1;
	
	// Contadores de derribos (knockdowns)
	int derribosClasico = 0;
	int derribosHitman = 0;

	// Variables para IA del Hitman en modo Solo
	Clock relojIAHitman;
	float tiempoProximaAccion = 0.0f;
	const float tiempoMinAccion = 0.3f;
	const float tiempoMaxAccion = 1.5f;
	int accionIAHitman = 0; // 0=idle, 1=atacar, 2=bloqueo, 3=movimiento

	auto configurarTransformacionesClasico = [&](AnimationClip* clip)
	{
		if (clip == nullptr)
		{
			return;
		}
		clip->setScale(escalaBoxeador, escalaBoxeador);
		const IntRect rectangulo = clip->sprite().getTextureRect();
		clip->setOrigin(static_cast<float>(rectangulo.width) * 0.5f, static_cast<float>(rectangulo.height));
		clip->setPosition(posicionBoxeador.x, posicionBoxeador.y);
	};

	auto configurarTransformacionesHitman = [&](AnimationClip* clip)
	{
		if (clip == nullptr)
		{
			return;
		}
		clip->setScale(-escalaHitman, escalaHitman);
		const IntRect rectangulo = clip->sprite().getTextureRect();
		clip->setOrigin(static_cast<float>(rectangulo.width) * 0.5f, static_cast<float>(rectangulo.height));
		clip->setPosition(posicionHitman.x, posicionHitman.y);
	};

	animacionReposo->setFrameTime(0.12f);
	animacionReposo->start(true);
	configurarTransformacionesClasico(animacionReposo);

	animacionJabReposo.setFrameTime(0.225f);
	animacionJabReposo.start(true);
	configurarTransformacionesClasico(&animacionJabReposo);
	animacionJabReposo.sprite().setColor(sf::Color(255, 255, 255, 200));

	hitmanReposo->setFrameTime(0.12f);
	hitmanReposo->start(true);
	configurarTransformacionesHitman(hitmanReposo);

	AnimationClip* animacionActual = animacionReposo;
	AnimationClip* animacionHitmanActual = hitmanReposo;

	auto reproducirAnimacionClasico = [&](const char* nombre, bool enBucle)
	{
		AnimationClip* nuevoClip = boxeadorClasico.clip(nombre);
		if (nuevoClip == nullptr)
		{
			return;
		}

		animacionActual = nuevoClip;
		nuevoClip->start(enBucle);
		configurarTransformacionesClasico(nuevoClip);
	};

	auto reproducirAnimacionHitman = [&](const char* nombre, bool enBucle)
	{
		AnimationClip* nuevoClip = boxeadorHitman.clip(nombre);
		if (nuevoClip == nullptr)
		{
			return;
		}

		animacionHitmanActual = nuevoClip;
		nuevoClip->start(enBucle);
		configurarTransformacionesHitman(nuevoClip);
	};

	auto actualizarIndicadores = [&]()
	{
		const float anchoEnergiaUnderClasico = static_cast<float>(texturaEnergiaClasicoDescargada.getSize().x) * escalaBarraEnergiaClasico;
		const float anchoVidaUnderClasico = static_cast<float>(texturaVidaClasicoDescargada.getSize().x) * escalaBarraVidaClasico;
		const float anchoEscudoUnderClasico = static_cast<float>(texturaEscudoClasicoDescargado.getSize().x) * escalaBarraEscudoClasico;
		const float totalAnchoClasico = anchoEnergiaUnderClasico + anchoVidaUnderClasico + anchoEscudoUnderClasico + (separacionIndicadores * 2.0f);
		const float posYClasico = posicionBoxeador.y + offsetIndicadoresInferior;
		const float baseXClasico = posicionBoxeador.x - (totalAnchoClasico * 0.5f);

		barraEnergiaClasicoDescargada.setPosition(baseXClasico, posYClasico);
		barraEnergiaClasicoProgreso.setPosition(baseXClasico, posYClasico);
		const float factorEnergiaClasico = std::clamp(energiaClasico / energiaMaximaClasico, 0.0f, 1.0f);
		barraEnergiaClasicoProgreso.setScale(escalaBarraEnergiaClasico * factorEnergiaClasico, escalaBarraEnergiaClasico);

		const float baseVidaClasico = baseXClasico + anchoEnergiaUnderClasico + separacionIndicadores;
		barraVidaClasicoDescargada.setPosition(baseVidaClasico, posYClasico);
		barraVidaClasicoProgreso.setPosition(baseVidaClasico, posYClasico);
		const float factorVidaClasico = std::clamp(vidaClasico / vidaMaximaClasico, 0.0f, 1.0f);
		barraVidaClasicoProgreso.setScale(escalaBarraVidaClasico * factorVidaClasico, escalaBarraVidaClasico);

		const float baseEscudoClasico = baseVidaClasico + anchoVidaUnderClasico + separacionIndicadores;
		barraEscudoClasicoDescargado.setPosition(baseEscudoClasico, posYClasico);
		barraEscudoClasicoProgreso.setPosition(baseEscudoClasico, posYClasico);
		const float factorEscudoClasico = std::clamp(escudoClasico / escudoMaximo, 0.0f, 1.0f);
		barraEscudoClasicoProgreso.setScale(escalaBarraEscudoClasico * factorEscudoClasico, escalaBarraEscudoClasico);

		const float anchoEnergiaUnderHitman = static_cast<float>(texturaEnergiaHitmanDescargada.getSize().x) * escalaBarraEnergiaHitman;
		const float anchoVidaUnderHitman = static_cast<float>(texturaVidaHitmanDescargada.getSize().x) * escalaBarraVidaHitman;
		const float anchoEscudoUnderHitman = static_cast<float>(texturaEscudoHitmanDescargado.getSize().x) * escalaBarraEscudoHitman;
		const float totalAnchoHitman = anchoEnergiaUnderHitman + anchoVidaUnderHitman + anchoEscudoUnderHitman + (separacionIndicadores * 2.0f);
		const float posYHitman = std::max(posicionHitman.y - offsetIndicadoresSuperior, 20.0f);
		const float baseXHitman = posicionHitman.x - (totalAnchoHitman * 0.5f);

		barraEnergiaHitmanDescargada.setPosition(baseXHitman, posYHitman);
		barraEnergiaHitmanProgreso.setPosition(baseXHitman, posYHitman);
		const float factorEnergiaHitman = std::clamp(energiaHitman / energiaMaximaHitman, 0.0f, 1.0f);
		barraEnergiaHitmanProgreso.setScale(escalaBarraEnergiaHitman * factorEnergiaHitman, escalaBarraEnergiaHitman);

		const float baseVidaHitman = baseXHitman + anchoEnergiaUnderHitman + separacionIndicadores;
		barraVidaHitmanDescargada.setPosition(baseVidaHitman, posYHitman);
		barraVidaHitmanProgreso.setPosition(baseVidaHitman, posYHitman);
		const float factorVidaHitman = std::clamp(vidaHitman / vidaMaximaHitman, 0.0f, 1.0f);
		barraVidaHitmanProgreso.setScale(escalaBarraVidaHitman * factorVidaHitman, escalaBarraVidaHitman);

		const float baseEscudoHitman = baseVidaHitman + anchoVidaUnderHitman + separacionIndicadores;
		barraEscudoHitmanDescargado.setPosition(baseEscudoHitman, posYHitman);
		barraEscudoHitmanProgreso.setPosition(baseEscudoHitman, posYHitman);
		const float factorEscudoHitman = std::clamp(escudoHitman / escudoMaximo, 0.0f, 1.0f);
		barraEscudoHitmanProgreso.setScale(escalaBarraEscudoHitman * factorEscudoHitman, escalaBarraEscudoHitman);
	};

	auto aplicarPosicionHitman = [&]()
	{
		const float limiteIzquierdo = 40.0f;
		const float limiteDerecho = static_cast<float>(dimensionesVentana.x) - 40.0f;
		const float limiteSuperior = static_cast<float>(dimensionesVentana.y) * 0.35f;
		const float limiteInferior = static_cast<float>(dimensionesVentana.y) * 0.85f;

		posicionHitman.x = std::clamp(posicionHitman.x, limiteIzquierdo, limiteDerecho);
		posicionHitman.y = std::clamp(posicionHitman.y, limiteSuperior, limiteInferior);

		configurarTransformacionesHitman(animacionHitmanActual);
		configurarTransformacionesHitman(hitmanReposo);
		actualizarIndicadores();
	};

	auto aplicarPosicionClasico = [&]()
	{
		const float limiteIzquierdo = 40.0f;
		const float limiteDerecho = static_cast<float>(dimensionesVentana.x) - 40.0f;
		const float limiteSuperior = static_cast<float>(dimensionesVentana.y) * 0.35f;
		const float limiteInferior = static_cast<float>(dimensionesVentana.y) * 0.85f;

		posicionBoxeador.x = std::clamp(posicionBoxeador.x, limiteIzquierdo, limiteDerecho);
		posicionBoxeador.y = std::clamp(posicionBoxeador.y, limiteSuperior, limiteInferior);

		configurarTransformacionesClasico(animacionActual);
		configurarTransformacionesClasico(animacionReposo);
		configurarTransformacionesClasico(&animacionJabReposo);
		actualizarIndicadores();
	};

	actualizarIndicadores();

	auto enRangoGolpe = [&]()
	{
		const float distanciaHorizontal = std::abs(posicionBoxeador.x - posicionHitman.x);
		const float distanciaVertical = std::abs(posicionBoxeador.y - posicionHitman.y);
		const float rangoHorizontal = 170.0f;
		const float rangoVertical = 120.0f;
		return distanciaHorizontal <= rangoHorizontal && distanciaVertical <= rangoVertical;
	};

	const float umbralDobleToque = 0.25f;
	const float desplazamientoPaso = 28.0f;
	const float desplazamientoDash = 70.0f;
	const float desplazamientoVertical = 35.0f;
	float instanteUltimoAbajo = -100.0f;
	bool bloqueoActivo = false;
	float instanteUltimaIzquierda = -100.0f;
	float instanteUltimaDerecha = -100.0f;
	float instanteUltimoHitmanAbajo = -100.0f;
	float instanteUltimaHitmanIzquierda = -100.0f;
	float instanteUltimaHitmanDerecha = -100.0f;
	bool bloqueoHitman = false;
	Clock relojEntrada;
	Clock relojDelta;
	Clock relojParpadeo;
	Clock relojKnockdown;
	bool mostrarTextoContinuar = true;
	const float intervaloParpadeo = 0.65f;
	
	// Pantalla de selección de modo de juego
	bool pantallaModoActiva = true;
	bool modoSolo = false; // true para Solo, false para 2 Jugadores
	int opcionSeleccionada = 0; // 0 para "Solo", 1 para "2 Jugadores"
	Clock relojParpadeoModo;
	bool mostrarSeleccionModo = true;
	
	bool pantallaCargaActiva = true;
	bool faseCuentaPrevia = true;
	float tiempoCuentaPrevia = 3.0f;
	int ultimoConteoPrevio = 3;
	bool campanaReproducida = false;

	// Estado de pausa por knockdown y fin de juego
	bool pausaPorKnockdown = false;
	float tiempoKnockdownRestante = 0.0f;
	int ultimoConteo = 0;
	bool juegoTerminado = false;
	string ganadorTexto = "K.O";
	Color colorGanador = Color::White;
	bool ultimoKnockdownRojo = false;
	bool ultimoKnockdownAzul = false;
	bool animacionKnockdownIniciadaRojo = false;
	bool animacionKnockdownIniciadaAzul = false;
	bool jugadorRojoEliminado = false;

	// Menú de opciones durante el combate
	bool pantallaOpcionesActiva = false;
	bool jugadorAzulEliminado = false;
	bool jugadorRojoGanador = false;
	bool jugadorAzulGanador = false;
	bool restaurarBloqueClasico = false;
	bool restaurarBloqueHitman = false;

	Text textoCuentaRegresiva;
	textoCuentaRegresiva.setFont(fuenteJuego);
	textoCuentaRegresiva.setCharacterSize(160);
	textoCuentaRegresiva.setFillColor(Color::White);
	const FloatRect limitesCuenta = textoCuentaRegresiva.getLocalBounds();
	textoCuentaRegresiva.setOrigin(limitesCuenta.left + (limitesCuenta.width * 0.5f), limitesCuenta.top + (limitesCuenta.height * 0.5f));
	textoCuentaRegresiva.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.42f);

	Text textoGameOver;
	textoGameOver.setFont(fuenteJuego);
	textoGameOver.setCharacterSize(96);
	textoGameOver.setFillColor(Color::White);

	Text textoReinicio;
	textoReinicio.setFont(fuenteJuego);
	textoReinicio.setCharacterSize(36);
	textoReinicio.setFillColor(Color::White);
	textoReinicio.setString("Presiona SPACE para reiniciar");

	Text textoPreviaPelea;
	textoPreviaPelea.setFont(fuenteJuego);
	textoPreviaPelea.setCharacterSize(52);
	textoPreviaPelea.setFillColor(Color::White);
	textoPreviaPelea.setString("La pelea comienza en...");

	Text textoCuentaPrevia;
	textoCuentaPrevia.setFont(fuenteJuego);
	textoCuentaPrevia.setCharacterSize(120);
	textoCuentaPrevia.setFillColor(Color::Yellow);
	textoCuentaPrevia.setString("3");

	// Menú de opciones durante el combate
	Text tituloOpciones;
	tituloOpciones.setFont(fuenteJuego);
	tituloOpciones.setCharacterSize(72);
	tituloOpciones.setFillColor(Color::Yellow);
	tituloOpciones.setString("OPCIONES");

	Text opcionReanudar;
	opcionReanudar.setFont(fuenteJuego);
	opcionReanudar.setCharacterSize(48);
	opcionReanudar.setFillColor(Color::White);
	opcionReanudar.setString("Reanudar Combate (O)");

	Text opcionVolverMenu;
	opcionVolverMenu.setFont(fuenteJuego);
	opcionVolverMenu.setCharacterSize(48);
	opcionVolverMenu.setFillColor(Color::White);
	opcionVolverMenu.setString("Salir del Juego (U)");

	Text indicadorOpciones;
	indicadorOpciones.setFont(fuenteJuego);
	indicadorOpciones.setCharacterSize(24);
	indicadorOpciones.setFillColor(Color::Cyan);
	indicadorOpciones.setString("Opciones (O)");

	Text instruccionesClasico;
	instruccionesClasico.setFont(fuenteJuego);
	instruccionesClasico.setString("Boxeador rojo (WASD, Q)");
	instruccionesClasico.setCharacterSize(28);
	instruccionesClasico.setFillColor(Color::Red);
	const FloatRect limitesInstruccionesClasico = instruccionesClasico.getLocalBounds();
	instruccionesClasico.setOrigin(limitesInstruccionesClasico.left, limitesInstruccionesClasico.top + (limitesInstruccionesClasico.height * 0.5f));
	instruccionesClasico.setPosition(24.0f, static_cast<float>(dimensionesVentana.y) - 40.0f);

	Text instruccionesHitman;
	instruccionesHitman.setFont(fuenteJuego);
	instruccionesHitman.setString("Boxeador azul (Flechas, Enter)");
	instruccionesHitman.setCharacterSize(28);
	instruccionesHitman.setFillColor(Color::Blue);
	const FloatRect limitesInstruccionesHitman = instruccionesHitman.getLocalBounds();
	instruccionesHitman.setOrigin(limitesInstruccionesHitman.width, limitesInstruccionesHitman.top + (limitesInstruccionesHitman.height * 0.5f));
	instruccionesHitman.setPosition(static_cast<float>(dimensionesVentana.x) - 24.0f, static_cast<float>(dimensionesVentana.y) - 40.0f);

	// Texto de Round
	Text textoRound;
	textoRound.setFont(fuenteJuego);
	textoRound.setString("ROUND 1");
	textoRound.setCharacterSize(48);
	textoRound.setFillColor(Color(220, 220, 220));
	const FloatRect limitesRound = textoRound.getLocalBounds();
	textoRound.setOrigin(limitesRound.left + (limitesRound.width * 0.5f), limitesRound.top);
	textoRound.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 20.0f);

	auto reiniciarPartida = [&]()
	{
		posicionBoxeador = posicionBoxeadorInicial;
		posicionHitman = posicionHitmanInicial;
		energiaClasico = energiaMaximaClasico;
		energiaHitman = energiaMaximaHitman;
		vidaClasico = vidaMaximaClasico;
		vidaHitman = vidaMaximaHitman;
		escudoClasico = escudoMaximo;
		escudoHitman = escudoMaximo;
		escudoClasicoActivo = false;
		escudoHitmanActivo = false;
		vidasClasico = 3;
		vidasHitman = 3;
		numeroRound = 1;
		derribosClasico = 0;
		derribosHitman = 0;
		bloqueoActivo = false;
		bloqueoHitman = false;
		instanteUltimoAbajo = -100.0f;
		instanteUltimaIzquierda = -100.0f;
		instanteUltimaDerecha = -100.0f;
		instanteUltimoHitmanAbajo = -100.0f;
		instanteUltimaHitmanIzquierda = -100.0f;
		instanteUltimaHitmanDerecha = -100.0f;
		jabReposoVisible = false;
		temporizadorJabReposo = 0.0f;
		indiceGolpe = 0;
		indiceGolpeHitman = 0;
		pausaPorKnockdown = false;
		tiempoKnockdownRestante = 0.0f;
		ultimoConteo = 0;
		ultimoKnockdownRojo = false;
		ultimoKnockdownAzul = false;
		animacionKnockdownIniciadaRojo = false;
		animacionKnockdownIniciadaAzul = false;
		jugadorRojoEliminado = false;
		jugadorAzulEliminado = false;
		jugadorRojoGanador = false;
		jugadorAzulGanador = false;
		restaurarBloqueClasico = false;
		restaurarBloqueHitman = false;
		juegoTerminado = false;
		ganadorTexto = "K.O";
		colorGanador = Color::White;
		animacionActual = animacionReposo;
		animacionHitmanActual = hitmanReposo;
		animacionActual->start(true);
		animacionHitmanActual->start(true);
		animacionJabReposo.start(true);
		configurarTransformacionesClasico(animacionReposo);
		configurarTransformacionesHitman(hitmanReposo);
		configurarTransformacionesClasico(&animacionJabReposo);
		textoCuentaRegresiva.setString("3");
		const FloatRect limKD = textoCuentaRegresiva.getLocalBounds();
		textoCuentaRegresiva.setOrigin(limKD.left + (limKD.width * 0.5f), limKD.top + (limKD.height * 0.5f));
		relojKnockdown.restart();
		actualizarIndicadores();
		faseCuentaPrevia = true;
		tiempoCuentaPrevia = 3.0f;
		ultimoConteoPrevio = 3;
		textoCuentaPrevia.setString("3");
		const FloatRect limCuentaInicial = textoCuentaPrevia.getLocalBounds();
		textoCuentaPrevia.setOrigin(limCuentaInicial.left + (limCuentaInicial.width * 0.5f), limCuentaInicial.top + (limCuentaInicial.height * 0.5f));
		campanaReproducida = false;
		relojEntrada.restart();
	};

	// Pantalla de menú principal
	while (ventanaRing.isOpen() && pantallaMenuActiva)
	{
		Event eventoMenu;
		while (ventanaRing.pollEvent(eventoMenu))
		{
			if (eventoMenu.type == Event::Closed)
			{
				ventanaRing.close();
			}
			else if (eventoMenu.type == Event::KeyPressed)
			{
				if (eventoMenu.key.code == Keyboard::A)
				{
					// Opción A: Jugar
					sonidoGolpe.play();
					pantallaMenuActiva = false;
					mostrarInstrucciones = false;
				}
				else if (eventoMenu.key.code == Keyboard::B)
				{
					// Opción 2: Instrucciones
					sonidoGolpe.play();
					pantallaMenuActiva = false;
					pantallaInstruccionesActiva = true;
					mostrarInstrucciones = true;
				}
			}
		}

		if (!ventanaRing.isOpen())
		{
			break;
		}

		if (relojParpadeoInstrucciones.getElapsedTime().asSeconds() >= 0.65f)
		{
			mostrarTextoContinuar = !mostrarTextoContinuar;
			relojParpadeoInstrucciones.restart();
		}

		ventanaRing.clear(Color::Black);
		ventanaRing.draw(lienzoRing);

		// Título del juego
		Text tituloPrincipal;
		tituloPrincipal.setFont(fuenteJuego);
		tituloPrincipal.setString("PUNCH OUT!");
		tituloPrincipal.setCharacterSize(128);
		tituloPrincipal.setFillColor(Color(220, 220, 220));
		const FloatRect limTitulo = tituloPrincipal.getLocalBounds();
		tituloPrincipal.setOrigin(limTitulo.left + (limTitulo.width * 0.5f), limTitulo.top + (limTitulo.height * 0.5f));
		tituloPrincipal.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 70.0f);

		// Mensaje de bienvenida
		Text mensajeBienvenida;
		mensajeBienvenida.setFont(fuenteJuego);
		mensajeBienvenida.setString("¡BIENVENIDO AL RING!");
		mensajeBienvenida.setCharacterSize(48);
		mensajeBienvenida.setFillColor(Color(160, 160, 160));
		const FloatRect limBienvenida = mensajeBienvenida.getLocalBounds();
		mensajeBienvenida.setOrigin(limBienvenida.left + (limBienvenida.width * 0.5f), limBienvenida.top + (limBienvenida.height * 0.5f));
		mensajeBienvenida.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 200.0f);

		// Opción 1: Jugar
		Text opcionJugar;
		opcionJugar.setFont(fuenteJuego);
		opcionJugar.setString("A. JUGAR");
		opcionJugar.setCharacterSize(52);
		opcionJugar.setFillColor(Color(180, 180, 180));
		const FloatRect limJugar = opcionJugar.getLocalBounds();
		opcionJugar.setOrigin(limJugar.left + (limJugar.width * 0.5f), limJugar.top + (limJugar.height * 0.5f));
		opcionJugar.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 350.0f);

		// Opción 2: Instrucciones
		Text opcionInstrucciones;
		opcionInstrucciones.setFont(fuenteJuego);
		opcionInstrucciones.setString("B. INSTRUCCIONES");
		opcionInstrucciones.setCharacterSize(52);
		opcionInstrucciones.setFillColor(Color(180, 180, 180));
		const FloatRect limInst = opcionInstrucciones.getLocalBounds();
		opcionInstrucciones.setOrigin(limInst.left + (limInst.width * 0.5f), limInst.top + (limInst.height * 0.5f));
		opcionInstrucciones.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 450.0f);

		// Atajos
		Text atajos;
		atajos.setFont(fuenteJuego);
		atajos.setString("(Presiona A para Jugar o B para Instrucciones)");
		atajos.setCharacterSize(24);
		atajos.setFillColor(Color(120, 120, 120));
		const FloatRect limAtajos = atajos.getLocalBounds();
		atajos.setOrigin(limAtajos.left + (limAtajos.width * 0.5f), limAtajos.top);
		atajos.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) - 120.0f);

		ventanaRing.draw(tituloPrincipal);
		ventanaRing.draw(mensajeBienvenida);
		ventanaRing.draw(opcionJugar);
		ventanaRing.draw(opcionInstrucciones);
		ventanaRing.draw(atajos);

		ventanaRing.display();
	}

	mostrarTextoContinuar = true;
	relojParpadeoInstrucciones.restart();

	if (!ventanaRing.isOpen())
	{
		return 0;
	}

	// Pantalla de instrucciones
	while (ventanaRing.isOpen() && pantallaInstruccionesActiva)
	{
		Event eventoInstrucciones;
		while (ventanaRing.pollEvent(eventoInstrucciones))
		{
			if (eventoInstrucciones.type == Event::Closed)
			{
				ventanaRing.close();
			}
			else if (eventoInstrucciones.type == Event::KeyPressed)
			{
				if (eventoInstrucciones.key.code == Keyboard::Space || eventoInstrucciones.key.code == Keyboard::Return)
				{
					sonidoGolpe.play();
					pantallaInstruccionesActiva = false;
				}
				else if (eventoInstrucciones.key.code == Keyboard::A)
				{
					sonidoGolpe.play();
					pantallaInstruccionesActiva = false;
					pantallaMenuActiva = true;
				}
			}
		}

		if (!ventanaRing.isOpen())
		{
			break;
		}

		if (relojParpadeoInstrucciones.getElapsedTime().asSeconds() >= 0.8f)
		{
			mostrarTextoContinuar = !mostrarTextoContinuar;
			relojParpadeoInstrucciones.restart();
		}

		ventanaRing.clear(Color::Black);
		ventanaRing.draw(lienzoRing);

		// Título del juego
		Text tituloPrincipal;
		tituloPrincipal.setFont(fuenteJuego);
		tituloPrincipal.setString("PUNCH OUT!");
		tituloPrincipal.setCharacterSize(96);
		tituloPrincipal.setFillColor(Color::Yellow);
		const FloatRect limTitulo = tituloPrincipal.getLocalBounds();
		tituloPrincipal.setOrigin(limTitulo.left + (limTitulo.width * 0.5f), limTitulo.top + (limTitulo.height * 0.5f));
		tituloPrincipal.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 60.0f);

		// Mensaje de bienvenida
		Text mensajeBienvenida;
		mensajeBienvenida.setFont(fuenteJuego);
		mensajeBienvenida.setString("¡BIENVENIDO AL RING!");
		mensajeBienvenida.setCharacterSize(48);
		mensajeBienvenida.setFillColor(Color::White);
		const FloatRect limBienvenida = mensajeBienvenida.getLocalBounds();
		mensajeBienvenida.setOrigin(limBienvenida.left + (limBienvenida.width * 0.5f), limBienvenida.top + (limBienvenida.height * 0.5f));
		mensajeBienvenida.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 160.0f);

		// Instrucciones generales
		Text instruccionesGenerales;
		instruccionesGenerales.setFont(fuenteJuego);
		instruccionesGenerales.setString("OBJETIVO: Derrotar al oponente 3 veces (K.O) para ganar");
		instruccionesGenerales.setCharacterSize(24);
		instruccionesGenerales.setFillColor(Color::Cyan);
		const FloatRect limGeneral = instruccionesGenerales.getLocalBounds();
		instruccionesGenerales.setOrigin(limGeneral.left, limGeneral.top);
		instruccionesGenerales.setPosition(40.0f, 240.0f);

		// Controles - Boxeador Rojo
		Text controlesClasicoTitulo;
		controlesClasicoTitulo.setFont(fuenteJuego);
		controlesClasicoTitulo.setString("BOXEADOR ROJO (Izquierda):");
		controlesClasicoTitulo.setCharacterSize(32);
		controlesClasicoTitulo.setFillColor(Color::Red);
		controlesClasicoTitulo.setPosition(40.0f, 300.0f);

		Text controlesClasicoDetalles;
		controlesClasicoDetalles.setFont(fuenteJuego);
		controlesClasicoDetalles.setString("  W = Saltar arriba      |      A = Retroceder      |      D = Avanzar\n  S = Bloqueo              |      Q = Atacar (Combos)");
		controlesClasicoDetalles.setCharacterSize(20);
		controlesClasicoDetalles.setFillColor(Color(255, 150, 150));
		controlesClasicoDetalles.setPosition(60.0f, 345.0f);

		// Controles - Boxeador Azul
		Text controlesHitmanTitulo;
		controlesHitmanTitulo.setFont(fuenteJuego);
		controlesHitmanTitulo.setString("BOXEADOR AZUL (Derecha):");
		controlesHitmanTitulo.setCharacterSize(32);
		controlesHitmanTitulo.setFillColor(Color::Blue);
		controlesHitmanTitulo.setPosition(40.0f, 430.0f);

		Text controlesHitmanDetalles;
		controlesHitmanDetalles.setFont(fuenteJuego);
		controlesHitmanDetalles.setString("  ↑ = Saltar arriba      |      ← = Retroceder      |      → = Avanzar\n  ↓ = Bloqueo              |      Enter = Atacar (Combos)");
		controlesHitmanDetalles.setCharacterSize(20);
		controlesHitmanDetalles.setFillColor(Color(150, 200, 255));
		controlesHitmanDetalles.setPosition(60.0f, 475.0f);

		// Consejos
		Text consejos;
		consejos.setFont(fuenteJuego);
		consejos.setString("CONSEJOS:\n• Mantén tu energia y usa el bloqueo para proteger tu escudo\n• Ataca cuando el oponente este cerca (rango de golpe)\n• La defensa es importante: bloquea los ataques enemigos");
		consejos.setCharacterSize(18);
		consejos.setFillColor(Color::Green);
		consejos.setPosition(60.0f, 565.0f);

		// Mensaje de continuar
		if (mostrarTextoContinuar)
		{
			Text mensajeContinuar;
			mensajeContinuar.setFont(fuenteJuego);
			mensajeContinuar.setString("Presiona SPACE para comenzar a jugar");
			mensajeContinuar.setCharacterSize(28);
			mensajeContinuar.setFillColor(Color::White);
			const FloatRect limCont = mensajeContinuar.getLocalBounds();
			mensajeContinuar.setOrigin(limCont.left + (limCont.width * 0.5f), limCont.top);
			mensajeContinuar.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) - 50.0f);
			ventanaRing.draw(mensajeContinuar);
		}

		ventanaRing.draw(tituloPrincipal);
		ventanaRing.draw(mensajeBienvenida);
		ventanaRing.draw(instruccionesGenerales);
		ventanaRing.draw(controlesClasicoTitulo);
		ventanaRing.draw(controlesClasicoDetalles);
		ventanaRing.draw(controlesHitmanTitulo);
		ventanaRing.draw(controlesHitmanDetalles);
		ventanaRing.draw(consejos);

		ventanaRing.display();
	}

	mostrarTextoContinuar = true;
	relojParpadeoInstrucciones.restart();

	if (!ventanaRing.isOpen())
	{
		return 0;
	}

	reiniciarPartida();

	// Pantalla de selección de modo de juego
	while (ventanaRing.isOpen() && pantallaModoActiva)
	{
		Event eventoModo;
		while (ventanaRing.pollEvent(eventoModo))
		{
			if (eventoModo.type == Event::Closed)
			{
				ventanaRing.close();
			}
			else if (eventoModo.type == Event::KeyPressed)
			{
				if (eventoModo.key.code == Keyboard::A)
				{
					sonidoGolpe.play();
					modoSolo = true;
					opcionSeleccionada = 0;
					pantallaModoActiva = false;
				}
				else if (eventoModo.key.code == Keyboard::B)
				{
					sonidoGolpe.play();
					modoSolo = false;
					opcionSeleccionada = 1;
					pantallaModoActiva = false;
				}
			}
		}

		if (!ventanaRing.isOpen())
		{
			break;
		}

		if (relojParpadeoModo.getElapsedTime().asSeconds() >= 0.65f)
		{
			mostrarSeleccionModo = !mostrarSeleccionModo;
			relojParpadeoModo.restart();
		}

		ventanaRing.clear(Color::Black);
		ventanaRing.draw(lienzoRing);

		// Título
		Text tituloModo;
		tituloModo.setFont(fuenteJuego);
		tituloModo.setString("SELECCIONAR MODO");
		tituloModo.setCharacterSize(96);
		tituloModo.setFillColor(Color(220, 220, 220));
		const FloatRect limTituloModo = tituloModo.getLocalBounds();
		tituloModo.setOrigin(limTituloModo.left + (limTituloModo.width * 0.5f), limTituloModo.top + (limTituloModo.height * 0.5f));
		tituloModo.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 100.0f);

		// Opción 1: Solo
		Text opcionSolo;
		opcionSolo.setFont(fuenteJuego);
		opcionSolo.setString("A. SOLO (vs IA)");
		opcionSolo.setCharacterSize(56);
		opcionSolo.setFillColor(Color::White);
		const FloatRect limSolo = opcionSolo.getLocalBounds();
		opcionSolo.setOrigin(limSolo.left + (limSolo.width * 0.5f), limSolo.top + (limSolo.height * 0.5f));
		opcionSolo.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 300.0f);

		// Nota de versión prueba para IA
		Text notaPrueba;
		notaPrueba.setFont(fuenteJuego);
		notaPrueba.setString("[VERSIÓN PRUEBA]");
		notaPrueba.setCharacterSize(20);
		notaPrueba.setFillColor(Color(255, 165, 0));
		const FloatRect limNotaPrueba = notaPrueba.getLocalBounds();
		notaPrueba.setOrigin(limNotaPrueba.left + (limNotaPrueba.width * 0.5f), limNotaPrueba.top);
		notaPrueba.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 365.0f);

		// Opción 2: 2 Jugadores
		Text opcion2Jugadores;
		opcion2Jugadores.setFont(fuenteJuego);
		opcion2Jugadores.setString("B. 2 JUGADORES");
		opcion2Jugadores.setCharacterSize(56);
		opcion2Jugadores.setFillColor(Color::Yellow);
		const FloatRect lim2J = opcion2Jugadores.getLocalBounds();
		opcion2Jugadores.setOrigin(lim2J.left + (lim2J.width * 0.5f), lim2J.top + (lim2J.height * 0.5f));
		opcion2Jugadores.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 450.0f);

		// Texto parpadeante de instrucciones
		Text instruccionesSeleccion;
		instruccionesSeleccion.setFont(fuenteJuego);
		instruccionesSeleccion.setString("(Presiona A o B para seleccionar)");
		instruccionesSeleccion.setCharacterSize(24);
		if (mostrarSeleccionModo)
		{
			instruccionesSeleccion.setFillColor(Color::Cyan);
		}
		else
		{
			instruccionesSeleccion.setFillColor(Color(100, 100, 100));
		}
		const FloatRect limInstrSel = instruccionesSeleccion.getLocalBounds();
		instruccionesSeleccion.setOrigin(limInstrSel.left + (limInstrSel.width * 0.5f), limInstrSel.top);
		instruccionesSeleccion.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, 620.0f);

		ventanaRing.draw(tituloModo);
		ventanaRing.draw(opcionSolo);
		ventanaRing.draw(notaPrueba);
		ventanaRing.draw(opcion2Jugadores);
		ventanaRing.draw(instruccionesSeleccion);

		ventanaRing.display();
	}

	mostrarSeleccionModo = true;
	relojParpadeoModo.restart();

	if (!ventanaRing.isOpen())
	{
		return 0;
	}

	while (ventanaRing.isOpen() && pantallaCargaActiva)
	{
		Event eventoCarga;
		while (ventanaRing.pollEvent(eventoCarga))
		{
			if (eventoCarga.type == Event::Closed)
			{
				ventanaRing.close();
			}
			else if (eventoCarga.type == Event::KeyPressed)
			{
				if (eventoCarga.key.code == Keyboard::Space)
				{
					sonidoGolpe.play();
					pantallaCargaActiva = false;
				}
			}
		}

		if (!ventanaRing.isOpen())
		{
			break;
		}

		if (relojParpadeo.getElapsedTime().asSeconds() >= intervaloParpadeo)
		{
			mostrarTextoContinuar = !mostrarTextoContinuar;
			relojParpadeo.restart();
		}

		ventanaRing.clear(Color::Black);
		ventanaRing.draw(lienzoRing);
		ventanaRing.draw(tituloJuego);
		if (mostrarTextoContinuar)
		{
			ventanaRing.draw(textoContinuar);
		}
		ventanaRing.display();
	}

	mostrarTextoContinuar = true;
	relojParpadeo.restart();
	musicaIntro.stop();
	musicaCombate.play();
	musicaIntensaActiva = false;

	if (!ventanaRing.isOpen())
	{
		return 0;
	}

	relojEntrada.restart();
	relojDelta.restart();
	relojParpadeo.restart();

	while (ventanaRing.isOpen())
	{
		const float segundosDelta = relojDelta.restart().asSeconds();
		animacionActual->update(segundosDelta);
		animacionJabReposo.update(segundosDelta);
		animacionHitmanActual->update(segundosDelta);
		
		// ===== LÓGICA DE IA PARA MODO SOLO =====
		if (modoSolo && !faseCuentaPrevia && !juegoTerminado && !pausaPorKnockdown)
		{
			tiempoProximaAccion -= segundosDelta;
			const float distanciaAlJugador = std::abs(posicionHitman.x - posicionBoxeador.x);
			
			if (tiempoProximaAccion <= 0.0f)
			{
				// Decidir siguiente acción
				const float factorVida = vidaHitman / vidaMaximaHitman;
				const float factorEnergia = energiaHitman / energiaMaximaHitman;
				
				// Probabilidades basadas en situación
				int accionRandomica = rand() % 100;
				
				if (distanciaAlJugador > 150.0f)
				{
					// Está lejos: acercarse
					accionIAHitman = 3; // Movimiento
				}
				else if (factorVida < 0.3f && factorEnergia >= 0.4f)
				{
					// Vida baja y energía disponible: atacar agresivamente
					accionIAHitman = 1; // Ataque
				}
				else if (accionRandomica < 40)
				{
					// 40% atacar
					if (factorEnergia >= 0.3f)
					{
						accionIAHitman = 1;
					}
					else
					{
						accionIAHitman = 0;
					}
				}
				else if (accionRandomica < 65)
				{
					// 25% bloquear
					if (factorVida < 0.5f)
					{
						accionIAHitman = 2; // Bloqueo defensivo
					}
					else
					{
						accionIAHitman = 3; // Movimiento
					}
				}
				else
				{
					// 35% movimiento
					accionIAHitman = 3;
				}
				
				tiempoProximaAccion = tiempoMinAccion + (rand() % 1000) * (tiempoMaxAccion - tiempoMinAccion) / 1000.0f;
			}
			
			// Ejecutar acción de IA
			switch (accionIAHitman)
			{
				case 1: // Ataque
				{
					if (energiaHitman >= costoGolpeHitman && distanciaAlJugador < 120.0f)
					{
						energiaHitman = std::max(0.0f, energiaHitman - costoGolpeHitman);
						sonidoGolpe.play();
						
						// Verificar si golpea al jugador
						const float distanciaAlGolpe = std::abs(posicionHitman.x - posicionBoxeador.x);
						if (distanciaAlGolpe < 100.0f)
						{
							if (bloqueoActivo && escudoClasico > 0.0f)
							{
								escudoClasico = std::max(0.0f, escudoClasico - 1.0f);
								reproducirAnimacionClasico("block-hit", false);
								restaurarBloqueClasico = true;
							}
							else
							{
								vidaClasico = std::max(0.0f, vidaClasico - danoGolpeRecibidoClasico);
								const int variante = rand() % 3;
								const char* danoAnim = (variante == 0 ? "damage-1" : (variante == 1 ? "damage-2" : "damage-3"));
								reproducirAnimacionClasico(danoAnim, false);
								
								if (vidaClasico <= 0.0f)
								{
									vidasClasico -= 1;
									derribosHitman++;
									if (vidasClasico > 0)
									{
										relojKnockdown.restart();
										pausaPorKnockdown = true;
										tiempoKnockdownRestante = 3.0f;
										ultimoConteo = 0;
										textoCuentaRegresiva.setString("3");
										const FloatRect limKD = textoCuentaRegresiva.getLocalBounds();
										textoCuentaRegresiva.setOrigin(limKD.left + (limKD.width * 0.5f), limKD.top + (limKD.height * 0.5f));
										ultimoKnockdownRojo = true;
										ultimoKnockdownAzul = false;
										animacionKnockdownIniciadaRojo = false;
									}
									else
									{
										reproducirAnimacionClasico("knockout", false);
										reproducirAnimacionHitman("win", true);
										sonidoKoFinal.play();
										juegoTerminado = true;
										ganadorTexto = "K.O";
										colorGanador = Color::Cyan;
										jugadorRojoEliminado = true;
										jugadorAzulGanador = true;
										// Volver a música normal cuando termina el juego
										if (musicaIntensaActiva)
										{
											musicaCombate2.stop();
											musicaCombate.play();
											musicaIntensaActiva = false;
										}
									}
								}
							}
						}
						
						const string& animacionGolpe = comboGolpesHitman[indiceGolpeHitman];
						reproducirAnimacionHitman(animacionGolpe.c_str(), false);
						indiceGolpeHitman = (indiceGolpeHitman + 1) % comboGolpesHitman.size();
					}
					break;
				}
				case 2: // Bloqueo
				{
					bloqueoHitman = true;
					escudoHitmanActivo = true;
					reproducirAnimacionHitman("block", true);
					break;
				}
				case 3: // Movimiento
				{
					if (distanciaAlJugador > 100.0f)
					{
						// Acercarse al jugador
						if (posicionHitman.x > posicionBoxeador.x)
						{
							posicionHitman.x -= desplazamientoPaso * 1.5f;
						}
						else
						{
							posicionHitman.x += desplazamientoPaso * 1.5f;
						}
						reproducirAnimacionHitman("forward-walk", false);
					}
					else
					{
						// Movimiento aleatorio alrededor del jugador
						if (rand() % 2 == 0)
						{
							posicionHitman.x -= desplazamientoPaso;
							reproducirAnimacionHitman("back-walk", false);
						}
						else
						{
							posicionHitman.x += desplazamientoPaso;
							reproducirAnimacionHitman("forward-walk", false);
						}
					}
					aplicarPosicionHitman();
					break;
				}
				default:
				{
					// Reposo
					if (bloqueoHitman)
					{
						bloqueoHitman = false;
						escudoHitmanActivo = false;
					}
					reproducirAnimacionHitman("idle", true);
					animacionHitmanActual = hitmanReposo;
					break;
				}
			}
		}
		
		// Alternar canciones de combate basado en derribos
		if (!faseCuentaPrevia && !juegoTerminado)
		{
			// Si algún jugador tiene 2 derribos (punto de KO), activar música intensa
			bool debeActivarMusicaIntensa = (derribosClasico >= 2 || derribosHitman >= 2);
			
			if (debeActivarMusicaIntensa && !musicaIntensaActiva)
			{
				// Cambiar a música intensa
				musicaCombate.stop();
				musicaCombate2.play();
				musicaIntensaActiva = true;
			}
			else if (!debeActivarMusicaIntensa && musicaIntensaActiva)
			{
				// Volver a música normal
				musicaCombate2.stop();
				musicaCombate.play();
				musicaIntensaActiva = false;
			}
		}
		
		if (faseCuentaPrevia)
		{
			tiempoCuentaPrevia = std::max(0.0f, tiempoCuentaPrevia - segundosDelta);
			const int conteo = static_cast<int>(std::ceil(tiempoCuentaPrevia));
			if (conteo != ultimoConteoPrevio)
			{
				ultimoConteoPrevio = conteo;
				textoCuentaPrevia.setString(std::to_string(std::max(1, conteo)));
				const FloatRect limPrevio = textoCuentaPrevia.getLocalBounds();
				textoCuentaPrevia.setOrigin(limPrevio.left + (limPrevio.width * 0.5f), limPrevio.top + (limPrevio.height * 0.5f));
			}
			if (tiempoCuentaPrevia <= 0.0f)
			{
				if (!campanaReproducida)
				{
					sonidoCampana.play();
					campanaReproducida = true;
				}
				faseCuentaPrevia = false;
			}
		}
		if (!faseCuentaPrevia)
		{
			energiaClasico = std::min(energiaMaximaClasico, energiaClasico + regeneracionEnergiaClasico * segundosDelta);
			energiaHitman = std::min(energiaMaximaHitman, energiaHitman + regeneracionEnergiaHitman * segundosDelta);
			if (!escudoClasicoActivo)
			{
				escudoClasico = std::min(escudoMaximo, escudoClasico + regenEscudoPorSegundo * segundosDelta);
			}
			if (!escudoHitmanActivo)
			{
				escudoHitman = std::min(escudoMaximo, escudoHitman + regenEscudoPorSegundo * segundosDelta);
			}
		}
		actualizarIndicadores();
		if (juegoTerminado)
		{
			if (relojParpadeo.getElapsedTime().asSeconds() >= intervaloParpadeo)
			{
				mostrarTextoContinuar = !mostrarTextoContinuar;
				relojParpadeo.restart();
			}
		}
		else
		{
			mostrarTextoContinuar = true;
		}

		if (restaurarBloqueClasico && bloqueoActivo && animacionActual->hasFinished())
		{
			reproducirAnimacionClasico("block", true);
			restaurarBloqueClasico = false;
		}
		else if (!jugadorRojoEliminado && !jugadorRojoGanador && !bloqueoActivo && animacionActual != animacionReposo && animacionActual->hasFinished())
		{
			reproducirAnimacionClasico("idle", true);
			animacionActual = animacionReposo;
		}

		if (restaurarBloqueHitman && bloqueoHitman && animacionHitmanActual->hasFinished())
		{
			reproducirAnimacionHitman("block", true);
			restaurarBloqueHitman = false;
		}
		else if (!jugadorAzulEliminado && !jugadorAzulGanador && !bloqueoHitman && animacionHitmanActual != hitmanReposo && animacionHitmanActual->hasFinished())
		{
			reproducirAnimacionHitman("idle", true);
			animacionHitmanActual = hitmanReposo;
		}

		if (animacionActual == animacionReposo && !bloqueoActivo)
		{
			temporizadorJabReposo += segundosDelta;
			if (jabReposoVisible)
			{
				if (temporizadorJabReposo >= duracionJabBreve)
				{
					jabReposoVisible = false;
					temporizadorJabReposo = 0.0f;
				}
			}
			else if (temporizadorJabReposo >= duracionReposoExtendida)
			{
				jabReposoVisible = true;
				animacionJabReposo.start(true);
				temporizadorJabReposo = 0.0f;
			}
		}
		else
		{
			jabReposoVisible = false;
			temporizadorJabReposo = 0.0f;
		}

		// Actualizar pausa por knockdown
		if (pausaPorKnockdown && !juegoTerminado)
		{
			const float elapsed = relojKnockdown.getElapsedTime().asSeconds();
			tiempoKnockdownRestante = std::max(0.0f, 3.0f - elapsed);
			int conteo = static_cast<int>(std::ceil(tiempoKnockdownRestante));
			conteo = std::max(1, conteo);
			if (conteo != ultimoConteo)
			{
				ultimoConteo = conteo;
				textoCuentaRegresiva.setString(std::to_string(conteo));
				const FloatRect lim = textoCuentaRegresiva.getLocalBounds();
				textoCuentaRegresiva.setOrigin(lim.left + (lim.width * 0.5f), lim.top + (lim.height * 0.5f));
			}

			if (conteo == 1)
			{
				if (ultimoKnockdownRojo && !animacionKnockdownIniciadaRojo)
				{
					animacionKnockdownIniciadaRojo = true;
					reproducirAnimacionClasico("knockdown", false);
				}
				if (ultimoKnockdownAzul && !animacionKnockdownIniciadaAzul)
				{
					animacionKnockdownIniciadaAzul = true;
					reproducirAnimacionHitman("knockdown", false);
				}
			}

			if (elapsed >= 3.0f)
			{
				pausaPorKnockdown = false;
				if (ultimoKnockdownRojo && vidasClasico > 0)
				{
					vidaClasico = vidaMaximaClasico;
					numeroRound++;
					textoRound.setString("ROUND " + std::to_string(numeroRound));
					const FloatRect limRound = textoRound.getLocalBounds();
					textoRound.setOrigin(limRound.left + (limRound.width * 0.5f), limRound.top);
					reproducirAnimacionClasico("idle", true);
					animacionActual = animacionReposo;
				}
				if (ultimoKnockdownAzul && vidasHitman > 0)
				{
					vidaHitman = vidaMaximaHitman;
					numeroRound++;
					textoRound.setString("ROUND " + std::to_string(numeroRound));
					const FloatRect limRound = textoRound.getLocalBounds();
					textoRound.setOrigin(limRound.left + (limRound.width * 0.5f), limRound.top);
					reproducirAnimacionHitman("idle", true);
					animacionHitmanActual = hitmanReposo;
				}
				ultimoKnockdownRojo = false;
				ultimoKnockdownAzul = false;
				animacionKnockdownIniciadaRojo = false;
				animacionKnockdownIniciadaAzul = false;
			}
		}

		Event eventoVentana;
		while (ventanaRing.pollEvent(eventoVentana))
		{
			if (eventoVentana.type == Event::Closed)
			{
				ventanaRing.close();
			}
			else if (eventoVentana.type == Event::KeyPressed)
			{
				// Permitir abrir/cerrar opciones en cualquier momento durante el combate
				if (eventoVentana.key.code == Keyboard::O && !faseCuentaPrevia && !juegoTerminado)
				{
					pantallaOpcionesActiva = !pantallaOpcionesActiva;
					continue;
				}
				// Volver al menú principal desde opciones
				if (eventoVentana.key.code == Keyboard::U && pantallaOpcionesActiva)
				{
					ventanaRing.close();
					continue;
				}
				// Permitir reiniciar cuando el juego ha terminado
				if (eventoVentana.key.code == Keyboard::Space && juegoTerminado)
				{
					sonidoGolpe.play();
					if (jugadorAzulGanador)
					{
						reproducirAnimacionHitman("win", true);
					}
					if (jugadorRojoGanador)
					{
						reproducirAnimacionClasico("win", true);
					}
					numeroRound++;
					textoRound.setString("ROUND " + std::to_string(numeroRound));
					const FloatRect limRound = textoRound.getLocalBounds();
					textoRound.setOrigin(limRound.left + (limRound.width * 0.5f), limRound.top);
					reiniciarPartida();
					relojEntrada.restart();
					relojDelta.restart();
					relojParpadeo.restart();
					continue;
				}
				// Resto de controles solo si no hay menú de opciones activo
				if (pantallaOpcionesActiva)
				{
					continue;
				}
				if (!pausaPorKnockdown && !juegoTerminado)
				{
					if (faseCuentaPrevia)
					{
						continue;
					}
					const float instante = relojEntrada.getElapsedTime().asSeconds();
					
					// Si estamos en modo solo, ignorar controles del Hitman
					bool esControlHitman = (eventoVentana.key.code == Keyboard::Left || 
											eventoVentana.key.code == Keyboard::Right || 
											eventoVentana.key.code == Keyboard::Up || 
											eventoVentana.key.code == Keyboard::Down || 
											eventoVentana.key.code == Keyboard::Enter);
					
					if (modoSolo && esControlHitman)
					{
						continue; // Ignorar estos controles en modo solo
					}
					
					switch (eventoVentana.key.code)
				{
				case Keyboard::Left:
				{
					const bool dobleToque = (instante - instanteUltimaHitmanIzquierda) <= umbralDobleToque;
					instanteUltimaHitmanIzquierda = instante;
					if (dobleToque)
					{
						reproducirAnimacionHitman("forward-dash", false);
						posicionHitman.x -= desplazamientoDash;
					}
					else
					{
						reproducirAnimacionHitman("forward-walk", false);
						posicionHitman.x -= desplazamientoPaso;
					}
					aplicarPosicionHitman();
					break;
				}
				case Keyboard::Right:
				{
					const bool dobleToque = (instante - instanteUltimaHitmanDerecha) <= umbralDobleToque;
					instanteUltimaHitmanDerecha = instante;
					if (dobleToque)
					{
						reproducirAnimacionHitman("back-dash", false);
						posicionHitman.x += desplazamientoDash;
					}
					else
					{
						reproducirAnimacionHitman("back-walk", false);
						posicionHitman.x += desplazamientoPaso;
					}
					aplicarPosicionHitman();
					break;
				}
				case Keyboard::Down:
				{
					instanteUltimoHitmanAbajo = instante;
					bloqueoHitman = true;
					escudoHitmanActivo = true;
					reproducirAnimacionHitman("block", true);
					aplicarPosicionHitman();
					break;
				}
				case Keyboard::Up:
				{
					posicionHitman.y -= desplazamientoVertical;
					aplicarPosicionHitman();
					break;
				}
				case Keyboard::Enter:
				{
					if (energiaHitman < costoGolpeHitman)
					{
						break;
					}
					energiaHitman = std::max(0.0f, energiaHitman - costoGolpeHitman);
					sonidoGolpe.play();
					if (enRangoGolpe())
					{
						if (bloqueoActivo && escudoClasico > 0.0f)
						{
							escudoClasico = std::max(0.0f, escudoClasico - 1.0f);
							reproducirAnimacionClasico("block-hit", false);
							restaurarBloqueClasico = true;
						}
						else
						{
							vidaClasico = std::max(0.0f, vidaClasico - danoGolpeRecibidoClasico);
							const int variante = rand() % 3;
							const char* danoAnim = (variante == 0 ? "damage-1" : (variante == 1 ? "damage-2" : "damage-3"));
							reproducirAnimacionClasico(danoAnim, false);
						}
						if (vidaClasico <= 0.0f)
						{
							vidasClasico -= 1;
							derribosHitman++;
							if (vidasClasico > 0)
							{
								relojKnockdown.restart();
								pausaPorKnockdown = true;
								tiempoKnockdownRestante = 3.0f;
								ultimoConteo = 0;
								textoCuentaRegresiva.setString("3");
								const FloatRect limKD = textoCuentaRegresiva.getLocalBounds();
								textoCuentaRegresiva.setOrigin(limKD.left + (limKD.width * 0.5f), limKD.top + (limKD.height * 0.5f));
								ultimoKnockdownRojo = true;
								ultimoKnockdownAzul = false;
								animacionKnockdownIniciadaRojo = false;
							}
							else
							{
								reproducirAnimacionClasico("knockout", false);
								reproducirAnimacionHitman("win", true);
								sonidoKoFinal.play();
								juegoTerminado = true;
								ganadorTexto = "K.O";
								colorGanador = Color::Blue;
								jugadorRojoEliminado = true;
								jugadorAzulGanador = true;
								// Volver a música normal cuando termina el juego
								if (musicaIntensaActiva)
								{
									musicaCombate2.stop();
									musicaCombate.play();
									musicaIntensaActiva = false;
								}
							}
						}
					}
					const string& animacionGolpe = comboGolpesHitman[indiceGolpeHitman];
					reproducirAnimacionHitman(animacionGolpe.c_str(), false);
					indiceGolpeHitman = (indiceGolpeHitman + 1) % comboGolpesHitman.size();
					aplicarPosicionHitman();
					break;
				}
				case Keyboard::A:
				{
					const bool dobleToque = (instante - instanteUltimaIzquierda) <= umbralDobleToque;
					instanteUltimaIzquierda = instante;
					if (dobleToque)
					{
						reproducirAnimacionClasico("back-dash", false);
						posicionBoxeador.x -= desplazamientoDash;
					}
					else
					{
						reproducirAnimacionClasico("back-walk", false);
						posicionBoxeador.x -= desplazamientoPaso;
					}
					aplicarPosicionClasico();
					break;
				}
				case Keyboard::D:
				{
					const bool dobleToque = (instante - instanteUltimaDerecha) <= umbralDobleToque;
					instanteUltimaDerecha = instante;
					if (dobleToque)
					{
						reproducirAnimacionClasico("forward-dash", false);
						posicionBoxeador.x += desplazamientoDash;
					}
					else
					{
						reproducirAnimacionClasico("forward-walk", false);
						posicionBoxeador.x += desplazamientoPaso;
					}
					aplicarPosicionClasico();
					break;
				}
				case Keyboard::S:
				{
					instanteUltimoAbajo = instante;
					bloqueoActivo = true;
					escudoClasicoActivo = true;
					reproducirAnimacionClasico("block", true);
					aplicarPosicionClasico();
					break;
				}
				case Keyboard::W:
				{
					posicionBoxeador.y -= desplazamientoVertical;
					aplicarPosicionClasico();
					break;
				}
				case Keyboard::Q:
				{
					if (energiaClasico < costoGolpeClasico)
					{
						break;
					}
					energiaClasico = std::max(0.0f, energiaClasico - costoGolpeClasico);
					sonidoGolpe.play();
					if (enRangoGolpe())
					{
						if (bloqueoHitman && escudoHitman > 0.0f)
						{
							escudoHitman = std::max(0.0f, escudoHitman - 1.0f);
							reproducirAnimacionHitman("block-hit", false);
							restaurarBloqueHitman = true;
						}
						else
						{
							vidaHitman = std::max(0.0f, vidaHitman - danoGolpeRecibidoHitman);
							const int variante = rand() % 3;
							const char* danoAnim = (variante == 0 ? "damage-1" : (variante == 1 ? "damage-2" : "damage-3"));
							reproducirAnimacionHitman(danoAnim, false);
						}
						if (vidaHitman <= 0.0f)
						{
							vidasHitman -= 1;
							derribosClasico++;
							if (vidasHitman > 0)
							{
								relojKnockdown.restart();
								pausaPorKnockdown = true;
								tiempoKnockdownRestante = 3.0f;
								ultimoConteo = 0;
								textoCuentaRegresiva.setString("3");
								const FloatRect limKD = textoCuentaRegresiva.getLocalBounds();
								textoCuentaRegresiva.setOrigin(limKD.left + (limKD.width * 0.5f), limKD.top + (limKD.height * 0.5f));
								ultimoKnockdownAzul = true;
								ultimoKnockdownRojo = false;
								animacionKnockdownIniciadaAzul = false;
							}
							else
							{
								reproducirAnimacionHitman("knockout", false);
								reproducirAnimacionClasico("win", true);
								sonidoKoFinal.play();
								juegoTerminado = true;
								ganadorTexto = "K.O";
								colorGanador = Color::Red;
								jugadorAzulEliminado = true;
								jugadorRojoGanador = true;
								// Volver a música normal cuando termina el juego
								if (musicaIntensaActiva)
								{
									musicaCombate2.stop();
									musicaCombate.play();
									musicaIntensaActiva = false;
								}
							}
						}
					}
					const string& animacionGolpe = comboGolpes[indiceGolpe];
					reproducirAnimacionClasico(animacionGolpe.c_str(), false);
					indiceGolpe = (indiceGolpe + 1) % comboGolpes.size();
					aplicarPosicionClasico();
					break;
				}
				default:
					break;
				}
				}
			}
			else if (eventoVentana.type == Event::KeyReleased)
			{
				if (eventoVentana.key.code == Keyboard::Down)
				{
					bloqueoHitman = false;
					restaurarBloqueHitman = false;
					escudoHitmanActivo = false;
					const float duracion = relojEntrada.getElapsedTime().asSeconds() - instanteUltimoHitmanAbajo;
					if (duracion <= umbralDobleToque)
					{
						posicionHitman.y += desplazamientoVertical;
					}
					if (!jugadorAzulGanador && !jugadorAzulEliminado)
					{
						reproducirAnimacionHitman("idle", true);
						animacionHitmanActual = hitmanReposo;
					}
					aplicarPosicionHitman();
				}
				else if (eventoVentana.key.code == Keyboard::S)
				{
					bloqueoActivo = false;
					restaurarBloqueClasico = false;
					escudoClasicoActivo = false;
					const float duracion = relojEntrada.getElapsedTime().asSeconds() - instanteUltimoAbajo;
					if (duracion <= umbralDobleToque)
					{
						posicionBoxeador.y += desplazamientoVertical;
					}
					if (!jugadorRojoGanador && !jugadorRojoEliminado)
					{
						reproducirAnimacionClasico("idle", true);
						animacionActual = animacionReposo;
					}
					aplicarPosicionClasico();
				}
			}
		}

		ventanaRing.clear(Color::Black);
		ventanaRing.draw(lienzoRing);
		ventanaRing.draw(animacionHitmanActual->sprite());
		if (jabReposoVisible && animacionActual == animacionReposo)
		{
			ventanaRing.draw(animacionJabReposo.sprite());
		}
		else
		{
			ventanaRing.draw(animacionActual->sprite());
		}
		ventanaRing.draw(barraEnergiaClasicoDescargada);
		if (energiaClasico > 0.0f)
		{
			ventanaRing.draw(barraEnergiaClasicoProgreso);
		}
		ventanaRing.draw(barraVidaClasicoDescargada);
		if (vidaClasico > 0.0f)
		{
			ventanaRing.draw(barraVidaClasicoProgreso);
		}
		ventanaRing.draw(barraEscudoClasicoDescargado);
		if (escudoClasico > 0.0f)
		{
			ventanaRing.draw(barraEscudoClasicoProgreso);
		}
		ventanaRing.draw(barraEnergiaHitmanDescargada);
		if (energiaHitman > 0.0f)
		{
			ventanaRing.draw(barraEnergiaHitmanProgreso);
		}
		ventanaRing.draw(barraVidaHitmanDescargada);
		if (vidaHitman > 0.0f)
		{
			ventanaRing.draw(barraVidaHitmanProgreso);
		}
		ventanaRing.draw(barraEscudoHitmanDescargado);
		if (escudoHitman > 0.0f)
		{
			ventanaRing.draw(barraEscudoHitmanProgreso);
		}
		const float corazonAncho = static_cast<float>(texturaCorazonLleno.getSize().x) * escalaCorazon;
		const float espacioCorazon = 18.0f;
		const float posYCorazones = static_cast<float>(dimensionesVentana.y) - 120.0f;
		auto dibujarCorazones = [&](int vidasRestantes, bool esRojo)
		{
			for (int i = 0; i < 3; ++i)
			{
				const bool lleno = i < vidasRestantes;
				Sprite sprite = esRojo
					? (lleno ? corazonRojoLleno : corazonRojoVacio)
					: (lleno ? corazonAzulLleno : corazonAzulVacio);
				if (esRojo)
				{
					sprite.setColor(lleno ? Color::Red : Color(255, 0, 0, 110));
				}
				else
				{
					const Color azulIntenso(180, 245, 255);
					const Color azulApagado(120, 200, 255, 155);
					sprite.setColor(lleno ? azulIntenso : azulApagado);
				}
				float posX = esRojo
					? (24.0f + static_cast<float>(i) * (corazonAncho + espacioCorazon))
					: (static_cast<float>(dimensionesVentana.x) - (corazonAncho + 24.0f) - static_cast<float>(i) * (corazonAncho + espacioCorazon));
				sprite.setPosition(posX, posYCorazones);
				ventanaRing.draw(sprite);
			}
		};
		
		// Función para dibujar contadores de derribos (knockdowns)
		auto dibujarDerribos = [&](int derribosRestantes, bool esRojo)
		{
			const float radioBolita = 8.0f;
			const float espacioBolitas = 22.0f;
			const Color colorRojo = Color::Red;
			const Color colorAzul = Color(180, 245, 255);
			
			for (int i = 0; i < 3; ++i)
			{
				const bool lleno = i < derribosRestantes;
				CircleShape bolita(radioBolita);
				
				if (esRojo)
				{
					bolita.setFillColor(lleno ? colorRojo : Color(255, 0, 0, 100));
				}
				else
				{
					bolita.setFillColor(lleno ? colorAzul : Color(180, 245, 255, 100));
				}
				
				float posX = esRojo
					? (24.0f + static_cast<float>(i) * espacioBolitas)
					: (static_cast<float>(dimensionesVentana.x) - (radioBolita * 2.0f + 24.0f) - static_cast<float>(i) * espacioBolitas);
				float posY = posYCorazones - 35.0f;
				
				bolita.setPosition(posX, posY);
				ventanaRing.draw(bolita);
			}
		};
		
		dibujarCorazones(vidasClasico, true);
		dibujarCorazones(vidasHitman, false);
		dibujarDerribos(derribosClasico, true);
		dibujarDerribos(derribosHitman, false);
		ventanaRing.draw(instruccionesClasico);
		ventanaRing.draw(instruccionesHitman);
		
		// Dibujar indicador de opciones en la parte superior derecha
		if (!faseCuentaPrevia && !juegoTerminado && !pantallaOpcionesActiva)
		{
			indicadorOpciones.setPosition(static_cast<float>(dimensionesVentana.x) - 200.0f, 20.0f);
			ventanaRing.draw(indicadorOpciones);
		}
		
		if (!faseCuentaPrevia && !juegoTerminado)
		{
			ventanaRing.draw(textoRound);
		}
		if (pausaPorKnockdown && !juegoTerminado)
		{
			ventanaRing.draw(textoCuentaRegresiva);
		}
		if (faseCuentaPrevia)
		{
			const FloatRect limPrevio = textoPreviaPelea.getLocalBounds();
			textoPreviaPelea.setOrigin(limPrevio.left + (limPrevio.width * 0.5f), limPrevio.top + (limPrevio.height * 0.5f));
			textoPreviaPelea.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.28f);
			ventanaRing.draw(textoPreviaPelea);
			const FloatRect limCuenta = textoCuentaPrevia.getLocalBounds();
			textoCuentaPrevia.setOrigin(limCuenta.left + (limCuenta.width * 0.5f), limCuenta.top + (limCuenta.height * 0.5f));
			textoCuentaPrevia.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.42f);
			ventanaRing.draw(textoCuentaPrevia);
		}
		if (juegoTerminado)
		{
			textoGameOver.setString(ganadorTexto);
			textoGameOver.setFillColor(colorGanador);
			unsigned int tamGameOver = 140;
			const float margenHorizontal = 40.0f;
			const float anchoMaximoTexto = static_cast<float>(dimensionesVentana.x) - (margenHorizontal * 2.0f);
			for (; tamGameOver >= 60; tamGameOver -= 4)
			{
				textoGameOver.setCharacterSize(tamGameOver);
				const FloatRect medida = textoGameOver.getLocalBounds();
				if (medida.width <= anchoMaximoTexto)
				{
					break;
				}
			}
			const FloatRect limGO = textoGameOver.getLocalBounds();
			textoGameOver.setOrigin(limGO.left + (limGO.width * 0.5f), limGO.top + (limGO.height * 0.5f));
			const float centroX = static_cast<float>(dimensionesVentana.x) * 0.5f;
			const float centroY = static_cast<float>(dimensionesVentana.y) * 0.5f;
			textoGameOver.setPosition(centroX, centroY);
			ventanaRing.draw(textoGameOver);
			if (mostrarTextoContinuar)
			{
				const FloatRect limReinicio = textoReinicio.getLocalBounds();
				textoReinicio.setOrigin(limReinicio.left + (limReinicio.width * 0.5f), limReinicio.top + (limReinicio.height * 0.5f));
				textoReinicio.setPosition(centroX, centroY + 90.0f);
				ventanaRing.draw(textoReinicio);
			}
		}
		
		// Dibujar menú de opciones si está activo
		if (pantallaOpcionesActiva)
		{
			// Fondo oscuro semi-transparente
			RectangleShape fondoOscuro(Vector2f(static_cast<float>(dimensionesVentana.x), static_cast<float>(dimensionesVentana.y)));
			fondoOscuro.setPosition(0.0f, 0.0f);
			fondoOscuro.setFillColor(Color(0, 0, 0, 200)); // Negro con transparencia
			ventanaRing.draw(fondoOscuro);
			
			// Título de opciones
			const FloatRect limTitulo = tituloOpciones.getLocalBounds();
			tituloOpciones.setOrigin(limTitulo.left + (limTitulo.width * 0.5f), limTitulo.top + (limTitulo.height * 0.5f));
			tituloOpciones.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.25f);
			ventanaRing.draw(tituloOpciones);
			
			// Opción 1: Reanudar
			const FloatRect limReanudar = opcionReanudar.getLocalBounds();
			opcionReanudar.setOrigin(limReanudar.left + (limReanudar.width * 0.5f), limReanudar.top + (limReanudar.height * 0.5f));
			opcionReanudar.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.45f);
			ventanaRing.draw(opcionReanudar);
			
			// Opción 2: Volver al menú
			const FloatRect limVolver = opcionVolverMenu.getLocalBounds();
			opcionVolverMenu.setOrigin(limVolver.left + (limVolver.width * 0.5f), limVolver.top + (limVolver.height * 0.5f));
			opcionVolverMenu.setPosition(static_cast<float>(dimensionesVentana.x) * 0.5f, static_cast<float>(dimensionesVentana.y) * 0.60f);
			ventanaRing.draw(opcionVolverMenu);
		}
		ventanaRing.display();
	}

	musicaCombate.stop();
	musicaCombate2.stop();

	return 0;
}
