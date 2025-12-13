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
	const float escalaRing = 2.5f;
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

	reiniciarPartida();

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
					reproducirAnimacionClasico("idle", true);
					animacionActual = animacionReposo;
				}
				if (ultimoKnockdownAzul && vidasHitman > 0)
				{
					vidaHitman = vidaMaximaHitman;
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
			else if (eventoVentana.type == Event::KeyPressed && !pausaPorKnockdown && !juegoTerminado)
			{
				if (faseCuentaPrevia)
				{
					continue;
				}
				const float instante = relojEntrada.getElapsedTime().asSeconds();
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
			else if (eventoVentana.type == Event::KeyPressed && juegoTerminado)
			{
				if (eventoVentana.key.code == Keyboard::Space)
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
					reiniciarPartida();
					relojEntrada.restart();
					relojDelta.restart();
					relojParpadeo.restart();
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
		dibujarCorazones(vidasClasico, true);
		dibujarCorazones(vidasHitman, false);
		ventanaRing.draw(instruccionesClasico);
		ventanaRing.draw(instruccionesHitman);
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
		ventanaRing.display();
	}

	return 0;
}
