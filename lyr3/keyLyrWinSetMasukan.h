// Bahasa Anak Indonesia untuk Komputer - BAIK
// Copyright Haris Hasanudin -  2005 - 2011
//
// Kupersembahkan untuk istriku tercinta Masako, anakku tersayang Takumi
// dan Tomoki serta seluruh putra putri Indonesia

// UTF-8

void keyWinSetMasukan ()
{

  char tmpMsg[MAX_STRING_LEN];
  int  n=0;

  VAL_LABEL valdat,tmpdat;
 
  // var list for class params
  char    class_tmpvar[MAX_STRING_LEN];

  memset(&valdat, '\0', sizeof(valdat));
  memset(&tmpdat, '\0', sizeof(tmpdat));

  memset(&class_tmpvar, '\0', sizeof(class_tmpvar));

  memset(tmpMsg, '\0', sizeof(tmpMsg));

  n = 0;

	do{

      memset(tmpMsg, '\0', sizeof(tmpMsg));

	  getlex();

	  switch( lex.type )
	    {
	    case TYPE_STR:
              if(n == 1) {
                strcpy(tmpMsg, lex.detail.string );
              } 
	      break;
	    
	    case TYPE_OBJECT:
              checkObjectValidation(lex.detail.object_str);
	    case TYPE_IDENT:

              if(currentClass != NULL && strlen(currentClass) > 0) {
               #ifdef WIN32
                #ifndef S_SPLINT_S
                sprintf_s(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #else
                snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
                #endif
               #else
               snprintf(class_tmpvar, sizeof(class_tmpvar),"%s->%s", currentClass, lex.detail.ident);
               #endif

                //printf("construct class var: %s\n", class_tmpvar);
                valdat = ValLabel( class_tmpvar, sub_deep, tmpdat, VAL_FLAG_SEARCH_R );

              } else {

                ungetlex();
                valdat = expression();
              }

              // printf("type %d\n", valdat.datatype);

              if(valdat.datatype == 3 || valdat.datatype == 44) { // teks or filename(Dialog)
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                } 
              } else if(valdat.datatype == 42 || valdat.datatype == 44) { // font & file dialog
                if(n == 1) {
                  strcpy(tmpMsg, valdat.str );
                } 
			  } else if(valdat.datatype == 40) {
                if(n == 0) {
				  tmpdat = valdat;
				  tmpdat.datatype = 40;
                } 
			  } else {
                Error("bentuk perintah Set_Masukan salah");
			  }

	      break;

	    default:
	      Error("bentuk perintah Set_Masukan salah");
	    }

        n++;

	    getlex();

	}while( lex.type == TYPE_SYM && lex.detail.symbol == ',');


    if(n != 2) {
      Error("parameter SET_MASUKAN tidak lengkap");
    } else {
	  if(tmpdat.GUItype == 5) { // Entry - Masukan
        gtk_entry_set_text(GTK_ENTRY(tmpdat.widget), tmpMsg);
	  } else {
	     Error("parameter Set_Masukan harus MASUKAN");
	  }
    }

	ungetlex();

}


