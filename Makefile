
all:
	@$(MAKE) -C Cub3D
	@$(MAKE) -C ft_printf
	@$(MAKE) -C libft
	@$(MAKE) -C libasm

fclean:
	@$(MAKE) -C Cub3D fclean
	@$(MAKE) -C ft_printf fclean
	@$(MAKE) -C libft fclean
	@$(MAKE) -C libasm fclean

