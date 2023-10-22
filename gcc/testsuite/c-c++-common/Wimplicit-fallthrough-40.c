/* { dg-do compile } */
/* { dg-options "-Wimplicit-fallthrough" } */

void bar (int);

void
foo (int i)
{
  switch (i)
    {
    case 1:
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    case 2:
      bar (1);
      break;
    case 3:
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
      #define A
      #undef A
    case 4:
      bar (1);
      break;
    #if A
    case 5:
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    #endif
    case 6:
      bar (1);
      break;
    case 7:
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    #define CASE8 case 8
    CASE8:
      bar (1);
      break;
    default:
      break;
    }
}

void
baz (int i)
{
  switch (i)
    {
    case 1:
      /* FT cleared by open brace.  */
      bar (1);			/* { dg-warning "statement may fall through" } */
      /* FALLTHROUGH */
      {}
    case 2:
      bar (1);
      break;
    case 3:
      /* FT cleared by semicolon.  */
      bar (1);			/* { dg-warning "statement may fall through" } */
      /* FALLTHROUGH */
      int a;
    case 4:
      bar (1);
      break;
    case 5:
      /* FT cleared by open brace inside macro.  */
#define CODE5 if (1) { }
      bar (1);			/* { dg-warning "statement may fall through" } */
      /* FALLTHROUGH */
      CODE5
    case 6:
      bar (1);
      break;
    case 7:
      /* FT cleared by semicolon inside macro.  */
#define CODE7 int b;
      bar (1);			/* { dg-warning "statement may fall through" } */
      /* FALLTHROUGH */
      CODE7
    case 8:
      bar (1);
      break;
    case 9:
      /* FT not preserved to next case */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    case 10:
      bar (1);			/* { dg-warning "statement may fall through" } */
    case 11:
      bar (1);
      break;
    case 12:
      /* Indirect fallthrough to default */
      bar (1);			/* { dg-warning "statement may fall through" } */
    case 13:
      /* Direct fallthrough to default */
      bar (1);			/* { dg-bogus "statement may fall through" } */
    default:
      break;
    }
}
