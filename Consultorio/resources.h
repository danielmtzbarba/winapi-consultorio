#pragma once

//{{NO_DEPENDENCIES}}
// Usado por windows.rc
//

//=======================
//VENTANA:INICI DE SESION
//=======================
#define IDD_INICIO_SESION               104
#define IDC_LBL_LOGIN_CEDULA            1110//ETIQUETA CEDULA
#define IDC_TXT_LOGIN_CEDULA            1005//INGRESAR CEDULA
#define IDC_LBL_LOGIN_PASS              1111//CONTRASE�A
#define IDC_TXT_LOGIN_PASS              1112//INGRESAR CONTRASE�A
#define IDC_BTN_LOGIN_ENTRAR            1113//BOTON INICIAR SESION
#define IDC_BTN_LOGIN_REGISTRAR         1114//BOTON PARA IR A LA CREACION DE USUARIO

#define IDC_BTN_USR_REGRESAR            1123


//======================
//VENTANA:GESTION DE CONSULTORIOS
//======================
#define IDD_CONSULTORIOS                108

//statics
#define IDC_LBL_CANTIDADDECON           1061//CANTIDAD DE CONSULTORIOS
#define IDC_LBL_DIASDISPO               1058//DIAS DISPONIBLES
#define IDC_LBL_HORARIODEAT             1059//HORARIO DE ATENCION
#define IDC_LBL_CONSULTORIO             1060//SELECCION DE CONSULTORIO
#define IDC_LBL_CONSENUSO               1063//CONSULTORIOS EN USO
#define IDC_LBL_DE_LUN                  1040
#define IDC_LBL_DE_MAR                  1041
#define IDC_LBL_DE_MIER                 1042
#define IDC_LBL_DE_JUEV                 1043
#define IDC_LBL_DE_VIER                 1044
#define IDC_LBL_DE_SAB                  1045
#define IDC_LBL_DE_DOM                  1046
#define IDC_LBL_GUION_LUN               1047
#define IDC_LBL_GUION_MAR               1048
#define IDC_IDC_LBL_GUION_MIER          1049
#define IDC_LBL_GUION_JUE               1050
#define IDC_LBL_GUION_VIER              1051
#define IDC_LBL_GUION_SAB               1052
#define IDC_LBL_GUION_DOM               1053

//CAJAS DE EDICION
#define IDC_TXT_CANTIDAD                1021//CANTIDAD DE CONSULTORIOS
#define IDC_TXT_HORA_INICIO_LUN         1054
#define IDC_TXT_HORA_FIN_LUN            1056
#define IDC_TXT_HORA_INICIO_MAR         1055
#define IDC_TXT_HORA_FIN_MAR            1057
#define IDC_TXT_HORA_INICIO_MIER        1009
#define IDC_TXT_HORA_FIN_MIER           1010
#define IDC_TXT_HORA_INICIO_JUE         1011
#define IDC_TXT_HORA_FIN_JUE            1012
#define IDC_TXT_HORA_INICIO_VIER        1013
#define IDC_TXT_HORA_FIN_VIER           1014
#define IDC_TXT_HORA_INICIO_SAB         1015
#define IDC_TXT_HORA_FIN_SAB            1016
#define IDC_TXT_HORA_INICIO_DOM         1017
#define IDC_TXT_HORA_FIN_DOM            1018

//CHECKBOXES
#define IDC_CHK_LUNES                   1033
#define IDC_CHK_MARTES                  1034
#define IDC_CHK_MIERCOLES               1035
#define IDC_CHK_JUEVES                  1036
#define IDC_CHK_VIERNES                 1037
#define IDC_CHK_SABADO                  1038
#define IDC_CHK_DOMINGO                 1039

//SPIN CONTROL
#define IDC_SPN_CANTIDAD                1032//CANTIDAD DE CONSULTORIOS

//LISTBOX
#define IDC_LST_CONSULTORIOS            1062//CANTIDAD DE CONSULTORIOS
#define IDC_LST_CONSULTORIOSGRANDE      1030//DONDE APARECERAN LOS CONSULTORIOS EN USO


//BOTONES
#define IDC_BTN_GUARDAR                 1064//GUARDAR INFORMACION
#define IDC_BTN_CERRAR                  1020//CIERRA VENTANA
#define IDC_BTN_LIMPIAR                 1019//LIMPIA HORARIOS
#define IDC_BTN_REGRESAR                1022



//============================
//VENTANA:CREACION DE USUARIOS
//============================
#define IDD_CREACION_USUARIO            3

//STATIC 
#define IDC_LBL_USR_NOMBRE              1115
#define IDC_LBL_USR_AP_PATERNO          1116//APELLIDO PATERNO
#define IDC_LBL_USR_AP_MATERNO          1117//APELLIDO MATERNO
#define IDC_LBL_USR_PASS                1118//CONTRASE�A(PASSWORD)
#define IDC_LBL_USR_CEDULA              1119//CEDULA DEL MEDICO

//CAJAS DE EDICION
#define IDC_TXT_USR_NOMBRE              1120
#define IDC_TXT_USR_AP_PATERNO          1121//APELLIDO PATERNO
#define IDC_TXT_USR_AP_MATERNO          1003//APELLIDO MATERNO
#define IDC_TXT_USR_PASS                1004//CONTRASE�A
#define IDC_TXT_USR_CEDULA              1007

//BOTON
#define IDC_BTN_USR_REGISTRAR           1122



//========================
//DATOS DEL PACIENTE
//=======================
#define IDD_DATOS_PACIENTE              116

//STATIC
#define IDC_LBL_PAC_ID                  1083
#define IDC_LBL_PAC_NOMBRE              1084
#define IDC_LBL_PAC_CORREO              1085
#define IDC_LBL_PAC_TELEFONO            1086
#define IDC_LBL_PAC_GENERO              1087
#define IDC_LBL_PAC_EDAD                1088

//CAJAS DE EDICION
#define IDC_TXT_PAC_ID                  1089
#define IDC_TXT_PAC_NOMBRE              1090
#define IDC_TXT_PAC_CORREO              1091
#define IDC_TXT_PAC_TELEFONO            1092
#define IDC_TXT_PAC_EDAD                1011

//COMBOBOX
#define IDC_CBX_PAC_GENERO              1093

//BOTONES
#define IDC_BTN_PAC_CONSULTAR           1094
#define IDC_BTN_PAC_ELIMINAR            1095
#define IDC_BTN_PAC_MODIFICAR           1096
#define IDC_BTN_PAC_REGRESAR            1097
#define IDC_BTN_PAC_AGREGAR             1009

#define IDC_TXT_PAC_AP_MATERNO          1100
#define IDC_TXT_PAC_AP_PATERNO          1098


//=======================
//RESERVACION DE CITAS
//=======================
#define IDD_RESERVACION_CITAS           112

//STATIC
#define IDC_LBL_CIT_ESPECIALIDAD        1098
#define IDC_LBL_CIT_MEDICO              1099
#define IDC_LBL_CIT_CONSULTORIO         1100
#define IDC_LBL_CIT_FECHA               1101
#define IDC_LBL_CIT_HORA                1102
#define IDC_LBL_CIT_PACIENTE            1103
#define IDC_LBL_CIT_ESTATUS             1104

//COMBOBOX
#define IDC_CBX_CIT_ESPECIALIDAD        1010
#define IDC_CBX_CIT_MEDICO              1011
#define IDC_CBX_CIT_CONSULTORIO         1014
#define IDC_CBX_CIT_PACIENTE            1012
#define IDC_CBX_CIT_ESTATUS             1016
#define IDC_CBX_CIT_HORA                1015

//CAJA DE EDICION
#define IDC_TXT_CIT_DIAGNOSTICO         1105

//DATE TIME CONTROL
#define IDC_DTP_CIT_FECHA               1013

//BOTONES
#define IDC_BTN_CIT_REGRESAR            1017
#define IDC_BTN_CIT_RESERVAR            1106
#define IDC_BTN_CIT_CONFIRMAR           1107
#define IDC_BTN_CIT_CANCELAR            1108
#define IDC_BTN_CIT_REG_DIAGNOSTICO     1109



//=======================
//MEDICOS
//=======================
#define IDD_GESTION_MEDICOS             118

//STATIC
#define IDC_LBL_MED_NOMBRE              1072
#define IDC_LBL_MED_CORREO              1073
#define IDC_LBL_MED_CEDULA              1074
#define IDC_LBL_MED_TELEFONO            1075
#define IDC_LBL_MED_ESPECIAL            1076//ESPECIALIDAD

//CAJAS DE EDICION
#define IDC_TXT_MED_NOMBRE              1077
#define IDC_TXT_MED_CEDULA              1078
#define IDC_TXT_MED_CORREO              1079
#define IDC_TXT_MED_TELEFONO            1008

#define IDC_TXT_MED_AP_PATERNO          1084
#define IDC_TXT_MED_AP_MATERNO          1086

//COMBOBOX
#define IDC_CBX_MED_ESPECIAL            1027

//BOTONES
#define IDC_BTN_MED_CONSULTAR           1012
#define IDC_BTN_MED_ELIMINAR            1082
#define IDC_BTN_MED_MODIFICAR           1081
#define IDC_BTN_MED_AGREGAR             1080
#define IDC_BTN_MED_REGRESAR            1013



//=======================
//MENU
//=======================
#define IDD_MENU_PRINCIPAL              106

//BOTONES
#define IDC_BTN_MENU_MEDICOS            1065
#define IDC_BTN_MENU_ESPECIALIDAD       1067
#define IDC_BTN_MENU_PACIENTES          1068
#define IDC_BTN_MENU_REPORTES           1069
#define IDC_BTN_MENU_AGENDAR            1070
#define IDC_BTN_MENU_CONSULTORIOS       1066
#define IDC_BTN_MENU_EDITAR_CITA        1014
#define IDC_BTN_MENU_LOGOUT             1071



//=======================
//ESPECIALIDADES
//=======================
#define IDD_GESTION_ESPECIALIDADES      110

//STATIC
#define IDC_LBL_ESP_DISPONIBLES         1123

//CAJA DE EDICION
#define IDC_TXT_ESP_NOMBRE              1001//SE ANOTARAN LAS ESPECIALIDADES

//BOTONES
#define IDC_BTN_ESP_AGREGAR             1124
#define IDC_BTN_ESP_REGRESAR            1125
#define IDC_BTN_ESP_ELIMINAR            1010



//=======================
//REPORTE DE CITAS
//=======================
#define IDD_REPORTE_CITAS               120

//STATIC
#define IDC_LBL_REP_ESP                 1126//ESPECIALIDADES
#define IDC_LBL_REP_FECHA_INI           1127//FECHA INICIAL
#define IDC_LBL_REP_FECHA_FIN           1128//FECHA FINAL

//COMBOBOX
#define IDC_LST_REP_ESP                 1131//ESPECIALIDAD

//CAJAS DE EDICION
#define IDC_TXT_REP_FECHA_INI           1129//FECHA INICIAL
#define IDC_TXT_REP_FECHA_FIN           1130//FECHA FINAL

//BOTONES
#define IDC_BTN_REP_BUSCAR              1132
#define IDC_BTN_REP_LIMPIAR             1133
#define IDC_BTN_REP_REGRESAR            1134
#define IDC_BTN_REP_GUARDAR             1135

//FALTA LISTVIEW, ESE LO HARE POR CODIGO SI NO TIENES TIEMPO

//=======================
//REPORTE MEDICOS
//=======================
#define IDD_REPORTE_MEDICOS             114

//STATIC
#define IDC_LBL_REPMED_ESPECIALIDAD     1136
#define IDC_LBL_REPMED_FECHA_INI        1137//FECHA INICIAL
#define IDC_LBL_REPMED_FECHA_FIN        1139//FECHA FINAL
#define IDC_LBL_REPMED_MEDICO           1138

//CAJAS DE EDICION
#define IDC_TXT_REPMED_FECHA_INI        1012//FECHA INICIAL
#define IDC_TXT_REPMED_MEDICO           1002
#define IDC_TXT_REPMED_FECHA_FIN        1013//FECHA FINAL

//COMBOBOX
#define IDC_CBX_REPMED_ESPECIALIDAD     1028

//BOTONES
#define IDC_BTN_REPMED_BUSCAR           1006
#define IDC_BTN_REPMED_LIMPIAR          1009
#define IDC_BTN_REPMED_REGRESAR         1007
#define IDC_BTN_REPMED_GUARDAR          1008

//FALTA LISTVIEW, ESE LO HARE POR CODIGO SI NO TIENES TIEMPO

//botones "basura" no los borres por si acaso
#define IDR_ACCELERATOR1                101
#define CU_VENTANAG                     102
#define IDD_DIALOG1                     104

#define IDD_DIALOG2                     106
#define IDD_DIALOG3                     108
#define IDD_DIALOG4                     110
#define IDD_DIALOG5                     112
#define IDD_DIALOG6                     114
#define IDD_DIALOG7                     116
#define IDD_DIALOG8                     118
#define IDD_DIALOG9                     120

#define IDC_DATETIMEPICKER1             1013


#define IDC_COMBOBOXEX1                 1027
#define IDC_SPIN2                       1032



// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        122
#define _APS_NEXT_COMMAND_VALUE         40002
#define _APS_NEXT_CONTROL_VALUE         1140
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif
