s_box = [0xc, 0x5, 0x6, 0xb, 0x9, 0x0, 0xa, 0xd, 0x3, 0xe, 0xf, 0x8, 0x4, 0x7, 0x1, 0x2]
inv_s_box = [5, 14, 15, 8, 12, 1, 2, 13, 11, 4, 6, 3, 0, 7, 9, 10]
p_box = [0, 16, 32, 48, 1, 17, 33, 49, 2, 18, 34, 50, 3, 19, 35, 51, 4, 20, 36, 52, 5, 21, 37, 53, 6, 22, 38, 54, 7, 23, 39, 55, 8, 24, 40, 56, 9, 25, 41, 57, 10, 26, 42, 58, 11, 27, 43, 59, 12, 28, 44, 60, 13, 29, 45, 61, 14, 30, 46, 62, 15, 31, 47, 63]
inv_p_box = [0, 4, 8, 12, 16, 20, 24, 28, 32, 36, 40, 44, 48, 52, 56, 60, 1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 2, 6, 10, 14, 18, 22, 26, 30, 34, 38, 42, 46, 50, 54, 58, 62, 3, 7, 11, 15, 19, 23, 27, 31, 35, 39, 43, 47, 51, 55, 59, 63]

def generate_round_keys128(key, number_of_rounds):
    roundkeys = []
    for round_counter in range(number_of_rounds): 
        roundkeys.append(key >> 64)
        key = ((key & (2 ** 67 - 1)) << 61) + (key >> 67)
        key = (s_box[key >> 124] << 124) + (s_box[(key >> 120)& 0xF] << 120) +  (key & (2 ** 120 - 1))
        key = key ^ (round_counter) << 62
    return roundkeys

def generate_round_keys80(key, number_of_rounds):
    roundkeys = []
    for round_counter in range(number_of_rounds):
        roundkeys.append(key >> 16)
        key = ((key & (2 ** 19 - 1)) << 61) + (key >> 19)
        key = (s_box[key >> 76] << 76) + (key & (2 ** 76 - 1))
        key = key ^ (round_counter) << 15
    return roundkeys


def add_round_key(current_state, round_key):
    return current_state ^ round_key

def sbox_layer_enc(state):
    s_output = 0
    for i in range(16):
        s_output += s_box[( state >> (i * 4)) & 0xF] << (i * 4)
    return s_output

def sbox_layer_dec(state):
    s_output = 0
    for i in range(16):
        s_output += inv_s_box[( state >> (i * 4)) & 0xF] << (i * 4)
    return s_output

def p_layer_enc(state):
    p_output = 0
    for i in range(64):
        p_output += ((state >> i) & 0x01) << p_box[i]
    return p_output

def p_layer_dec(state):
    p_output = 0
    for i in range(64):
        p_output += ((state >> i) & 0x01) << inv_p_box[i]
    return p_output

def number_to_string(i):
    string = '%0*x' % (16, i)
    return string.decode('hex')

def present_encrypt(number_of_rounds, key_schedule, plain_text):
    current_state = plain_text
    for round_counter in range(number_of_rounds - 1):
        current_state = add_round_key(current_state, key_schedule[round_counter])
        current_state = sbox_layer_enc(current_state)
        current_state = p_layer_enc(current_state)
    encrypted_state  = add_round_key(current_state, key_schedule[-1])
    return number_to_string(encrypted_state)

def present_decrypt(number_of_rounds, key_schedule, plain_text):
    current_state = int(plain_text.encode('hex'), 16)
    for round_counter in range(number_of_rounds - 1):
        current_state = add_round_key(current_state, key_schedule[-round_counter - 1])
        current_state = p_layer_dec(current_state)
        current_state = sbox_layer_dec(current_state)
    decrypted_state = add_round_key(current_state, key_schedule[0])
    return number_to_string(decrypted_state)

def present():
    key_80 = 0X2d3c4b5a6978afed09a2
    key_128 = 0Xdb5490480f1e2d3c4b5a6978afed09a2
    print("Key 80", hex(key_80))
    number_of_rounds = 32
    key_schedule = generate_round_keys80(key_80, number_of_rounds)
    plain_text1 = 0X797368656c646f6e
    print("Hex Format of Plain Text1", hex(plain_text1))
    encrypted_text1 = present_encrypt(number_of_rounds, key_schedule, plain_text1)
    print("Encrypter Text", encrypted_text1.encode('hex'))
    decrypted_text1 = present_decrypt(number_of_rounds, key_schedule, encrypted_text1)
    print("Decrypted Text", decrypted_text1)
    plain_text2 = 0X73616e646965676f
    print("Hex Format of Plain Text2", hex(plain_text2))
    encrypted_text2 = present_encrypt(number_of_rounds, key_schedule, plain_text2)
    print("Encrypter Text", encrypted_text2.encode('hex'))
    decrypted_text2 = present_decrypt(number_of_rounds, key_schedule, encrypted_text2)
    print("Decrypted Text", decrypted_text2)
    plain_text3 = 0X6368657363616b65
    print("Hex Format of Plain Text3", hex(plain_text3))
    encrypted_text3 = present_encrypt(number_of_rounds, key_schedule, plain_text3)
    print("Encrypter Text", encrypted_text3.encode('hex'))
    decrypted_text3 = present_decrypt(number_of_rounds, key_schedule, encrypted_text3)
    print("Decrypted Text", decrypted_text3)
    plain_text4 = 0X746f6d6a65727279
    print("Hex Format of Plain Text4", hex(plain_text4))
    encrypted_text4 = present_encrypt(number_of_rounds, key_schedule, plain_text4)
    print("Encrypter Text", encrypted_text4.encode('hex'))
    decrypted_text4 = present_decrypt(number_of_rounds, key_schedule, encrypted_text4)
    print("Decrypted Text", decrypted_text4)
    plain_text5 = 0X6861636b726d616e
    print("Hex Format of Plain Text5", hex(plain_text5))
    encrypted_text5 = present_encrypt(number_of_rounds, key_schedule, plain_text5)
    print("Encrypter Text", encrypted_text5.encode('hex'))
    decrypted_text5 = present_decrypt(number_of_rounds, key_schedule, encrypted_text5)
    print("Decrypted Text", decrypted_text5)
    print("Key 128", hex(key_128))
    number_of_rounds = 32
    key_schedule = generate_round_keys128(key_128, number_of_rounds)
    plain_text1 = 0X797368656c646f6e
    print("Hex Format of Plain Text1", hex(plain_text1))
    encrypted_text1 = present_encrypt(number_of_rounds, key_schedule, plain_text1)
    print("Encrypter Text", encrypted_text1.encode('hex'))
    decrypted_text1 = present_decrypt(number_of_rounds, key_schedule, encrypted_text1)
    print("Decrypted Text", decrypted_text1)
    plain_text2 = 0X73616e646965676f
    print("Hex Format of Plain Text2", hex(plain_text2))
    encrypted_text2 = present_encrypt(number_of_rounds, key_schedule, plain_text2)
    print("Encrypter Text", encrypted_text2.encode('hex'))
    decrypted_text2 = present_decrypt(number_of_rounds, key_schedule, encrypted_text2)
    print("Decrypted Text", decrypted_text2)
    plain_text3 = 0X6368657363616b65
    print("Hex Format of Plain Text3", hex(plain_text3))
    encrypted_text3 = present_encrypt(number_of_rounds, key_schedule, plain_text3)
    print("Encrypter Text", encrypted_text3.encode('hex'))
    decrypted_text3 = present_decrypt(number_of_rounds, key_schedule, encrypted_text3)
    print("Decrypted Text", decrypted_text3)
    plain_text4 = 0X746f6d6a65727279
    print("Hex Format of Plain Text4", hex(plain_text4))
    encrypted_text4 = present_encrypt(number_of_rounds, key_schedule, plain_text4)
    print("Encrypter Text", encrypted_text4.encode('hex'))
    decrypted_text4 = present_decrypt(number_of_rounds, key_schedule, encrypted_text4)
    print("Decrypted Text", decrypted_text4)
    plain_text5 = 0X6861636b726d616e
    print("Hex Format of Plain Text5", hex(plain_text5))
    encrypted_text5 = present_encrypt(number_of_rounds, key_schedule, plain_text5)
    print("Encrypter Text", encrypted_text5.encode('hex'))
    decrypted_text5 = present_decrypt(number_of_rounds, key_schedule, encrypted_text5)
    print("Decrypted Text", decrypted_text5)


present()
