inline u8 matrix_get(const u8* values, s32 width, s32 row, s32 col);

inline u8 tetrino_get(const Tetrino* tetrino, s32 row, s32 col, s32 rotation);

bool check_piece_valid(const Piece_State* piece,
    const u8* board, s32 width, s32 height);

void spawn_piece(Game_State* game);

void update_game(Game_State* game,
    const Input_State* input);