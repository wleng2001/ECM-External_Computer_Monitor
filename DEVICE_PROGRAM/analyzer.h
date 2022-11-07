class edit_text {
  public:
    String rewrite_in_range(byte start, byte end, String data) {
      String new_data = "";
      if (end < 0) {
        return "";
      }
      for (byte i = start; i <= end; i = i + 1) {
        new_data += String(data[i]);
      }
      return new_data;
    }

    String delete_spaces(String data) {
      byte i = 0;
      String analize_char = "" + String(data[0]);
      String new_data = "";
      while (analize_char == " ") {
        i = i + 1;
        analize_char = String(data[i]);
      }

      for (byte j = i; j < data.length(); j = j + 1) {
        new_data += String(data[j]);
      }
      return new_data;
    }

    String rm_comment(String data) {
      String new_data = "";
      for (byte i = 0; i < data.length(); i = i + 1) {
        if (String(data[i]) == "'") {
          return new_data;
        }
        new_data += String(data[i]);
      }
      return new_data;
    }


};
edit_text ed_txt;

String delete_useless_spaces(String data) {
  data = ed_txt.rm_comment(data);
  data = ed_txt.delete_spaces(data);
  data.trim();
  bool pre_spaces = false;
  bool start_quote = false;
  byte i = 0;
  String temporary_data = "";
  while (i < data.length()) {
    if (String(data[i]) == "\"") {
      start_quote = !start_quote;
    }
    if (String(data[i]) == " " and start_quote == false and pre_spaces == true) {
      //data=ed_txt.rewrite_in_range(0,i,data)+ed_txt.delete_spaces(ed_txt.rewrite_in_range(i,data.length(),data));
    } else {
      temporary_data += String(data[i]);
      if (String(data[i]) == " ") {
        pre_spaces = true;
      } else {
        pre_spaces = false;
      }
    }
    i++;
  }
  data = temporary_data;
  return data;
}

String one_word_ret(String data){
  String comm="";
  bool start_quote=false;
  if(String(data[0])=="\""){
    start_quote!=start_quote;  
  }
  for(byte i=0; i<data.length();i++){
    if(i>=data.length() or (String(data[i])==" " and start_quote==false)){
      comm.toUpperCase();
      return comm;
    }
    if(String(data[i])=="\""){
      start_quote!=start_quote;  
    }
    comm+=String(data[i]);
  }
  comm.toUpperCase();
  return comm;
}
