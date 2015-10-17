int receiverEvent(myIrrlicht_ *ir)
{
    if(ir->receiver.IsKeyDown(KEY_ESCAPE))
    {
        return 0x01;
    }

    if(ir->receiver.IsKeyDown((EKEY_CODE)0x51) || ir->receiver.IsKeyDown((EKEY_CODE)24) )//q
    {
        return 0x51;
    }

    if(ir->receiver.IsKeyDown((EKEY_CODE)0x45) || ir->receiver.IsKeyDown((EKEY_CODE)26) )//e
    {
        return 0x45;
    }

    if(ir->receiver.IsKeyDown((EKEY_CODE)0x52) || ir->receiver.IsKeyDown((EKEY_CODE)27) )//r
    {
        return 0x52;
    }

    if(ir->receiver.IsKeyDown((EKEY_CODE)0x44) || ir->receiver.IsKeyDown((EKEY_CODE)40) )//d
    {
        return 0x44;
    }
    if(ir->receiver.IsKeyDown((EKEY_CODE)0x41) || ir->receiver.IsKeyDown((EKEY_CODE)38) )//a
    {
        return 0x41;
    }
    if(ir->receiver.IsKeyDown((EKEY_CODE)0x53) || ir->receiver.IsKeyDown((EKEY_CODE)39) )//s
    {
        return 0x53;
    }
    if(ir->receiver.IsKeyDown((EKEY_CODE)0x57) || ir->receiver.IsKeyDown((EKEY_CODE)25) )//w
    {
        return 0x57;
    }
    if(ir->receiver.IsKeyDown((EKEY_CODE)0x0D) )//enter
    {
        return 0x0d;
    }
    return 0;
}
