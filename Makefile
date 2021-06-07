all:
	clang tcp_chat_client.c -o ctest

fclean:
	rm ctest
