void helo(void) {
    output(233);
    helo();
}
void func(void) {
    output(3);
    output(2);
    helo();
}
void main(void) {
    output(7);
    func();
    output(6);
}
