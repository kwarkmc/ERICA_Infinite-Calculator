int check_parenthese(char *in) {
  StackType s;
  char ch, open_ch;
  int i, n = strlen(in);
  init(&s);

  for(i = 0;i < n;i++) {
    ch = in[i];
    switch(ch) {
      case'(':case'[':case'{':
        push(&s, ch);
        break;
      case')':case'}':case']':
        if(is_empty(&s))
          return false;
        else {
          open_ch = pop(&s);
          if((open_ch == '(' && ch != ')') || (open_ch == '[' && ch != ']') || (open_ch == '{' && ch != '}'))
            return false;
          break;
        }
        
    }
  }
  if(!is_empty(&s))
    return false;
  return true;
}
