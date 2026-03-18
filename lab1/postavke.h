#pragma once

#define PROJEKT		"Makefile-lab"
#define AUTOR		"Student-osura"

enum {
	UCITAJ_IZ_DATOTEKE = 0,
	UCITAJ_S_TIPKOVNICE,
	GENERIRAJ_ULAZ,
	OBRADI_POBROJI,
	OBRADI_SMISAO,
	OBRADI_SMISAO_NA_BRZINU,
	OBRADI_SMISAO_DUBLJE,
	SPREMI_U_DATOTEKU,
	ISPISI_NA_ZASLON
};

#define ZASTAVICA(ZAST) (1<<(ZAST))

#define DATOTEKA_ULAZ  "ulaz.txt"
#define DATOTEKA_IZLAZ  "izlaz.txt"

#define BR_RIJECI	8
#define RIJECI		{"macka", "pas", "riba", "vuk", "auto", "juha", "fer", "šum"}
