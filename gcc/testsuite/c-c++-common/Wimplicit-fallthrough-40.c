/* { dg-do compile } */
/* { dg-options "-Wimplicit-fallthrough" } */

void bar (int);

void
foo (int i)
{
  switch (i)
    {
    case 1:
      /* Common fallthrough situation.  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    case 2:
      bar (1);
      break;
    case 3:
      /* Directives after fallthrough.  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
      #define A
      #undef A
    case 4:
      bar (1);
      break;
    case 5:
    case 6:
    case 7:
    case 8:
      /* Case label inside macro.  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
      #define CASE9 case 9
    CASE9:
      bar (1);
      break;
    case 10:
      /* FT comment inside macro.  */
      #define CODE10 /* Fallthrough */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      CODE10
    case 11:
      /* FT comment before conditional directive.  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    #if 1
    case 12:
      /* Switch case inside conditional directive.  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
      /* FALLTHROUGH */
    #endif
    case 13:
      bar (1);
      break;
    case 14:
      /* FT comment inside conditional directive (true).  */
      bar (1);			/* { dg-bogus "statement may fall through" } */
    #if 1
      /* FALLTHROUGH */
    #endif
    case 15:
      bar (1);
      break;
    case 16:
      /* FT comment inside conditional directive (false).  */
      bar (1);			/* { dg-warning "statement may fall through" } */
    #if 0
      /* FALLTHROUGH */
    #endif
    case 17:
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
      /* FT cleared by open brace inside macro. Correct behaviour is WARNING GIVEN.  */
#define CODE5 if (1) { }
      bar (1);			/* { dg-warning "statement may fall through" "Parser problem??? WORKS WITH C++ BUT NOT C!!!" } */
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
      /* FT at end of block */
      {
        bar (1);
	/* FALLTHROUGH */	/* { dg-bogus "statement may fall through" } */
      }
    case 13:
      /* Indirect fallthrough to default */
      bar (1);			/* { dg-warning "statement may fall through" } */
    case 14:
      /* Direct fallthrough to default */
      bar (1);			/* { dg-bogus "statement may fall through" } */
    default:
      break;
    }
}
