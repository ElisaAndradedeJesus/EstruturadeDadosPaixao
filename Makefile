# Este Makefile tem como função facilitar a atualização do repositório 
# independente que criei apenas para que ao entregar o trabalho o professor 
# receba um epositório mais limpo ao invés dessa bagunça de pastas.

# Estou utilizando git subtree pra manter a conexão dos dois repositórios

# Lembrar sempre de dar comit/push no repositório principal primeiro(esse)

.PHONY: sync-campeonato

sync-campeonato:
	git subtree push --prefix=CampeonatoComputacionaldeFutebol_ElisadeJesus \
	https://github.com/ElisaAndradedeJesus/CampeonatoComputacionaldeFutebol_ElisadeJesus.git \
	main
