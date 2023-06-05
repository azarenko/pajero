#include <idc.idc>
#include <memcpy.idc>



static main() {

MakeName(0xFEC0,"SCI3_SMR");
MakeName(0xFEC1,"SCI3_BRR");
MakeName(0xFEC2,"SCI3_SCR");
MakeName(0xFEC3,"SCI3_TDR");
MakeName(0xFEC4,"SCI3_SSR");
MakeName(0xFEC5,"SCI3_RDR");


MakeName(0xFEC8,"SCI1_SMR");
MakeName(0xFEC9,"SCI1_BRR");
MakeName(0xFECA,"SCI1_SCR");
MakeName(0xFECB,"SCI1_TDR");
MakeName(0xFECC,"SCI1_SSR");
MakeName(0xFECD,"SCI1_RDR");

MakeName(0xFED0,"SCI2_SMR");
MakeName(0xFED1,"SCI2_BRR");
MakeName(0xFED2,"SCI2_SCR");
MakeName(0xFED3,"SCI2_TDR");
MakeName(0xFED4,"SCI2_SSR");
MakeName(0xFED5,"SCI2_RDR");

MakeName(0xFE80,"P1DDR");
MakeName(0xFE81,"P2DDR");
MakeName(0xFE82,"P1DR");
MakeName(0xFE83,"P2DR");
MakeName(0xFE84,"P3DDR");
MakeName(0xFE85,"P4DDR");
MakeName(0xFE86,"P3DR");
MakeName(0xFE87,"P4DR");
MakeName(0xFE88,"P5DDR");
MakeName(0xFE89,"P6DDR");
MakeName(0xFE8A,"P5DR");
MakeName(0xFE8B,"P6DR");
MakeName(0xFE8C,"P7DDR");
MakeName(0xFE8E,"P7DR");
MakeName(0xFE8F,"P8DR");

MakeName(0xFE91,"PADDR");
MakeName(0xFE92,"P9DR");
MakeName(0xFE93,"PADR");
MakeName(0xFE94,"PBDDR");
MakeName(0xFE95,"PCDDR");
MakeName(0xFE96,"PBDR");
MakeName(0xFE97,"PCDR");
MakeName(0xFE98,"PBPCR");
MakeName(0xFE99,"PCPCR");
MakeName(0xFE9A,"oCR");

MakeName(0xFEA0,"ADDR0H");
MakeName(0xFEA1,"ADDR0L");
MakeName(0xFEA2,"ADDR1H");
MakeName(0xFEA3,"ADDR1L");
MakeName(0xFEA4,"ADDR2H");
MakeName(0xFEA5,"ADDR2L");
MakeName(0xFEA6,"ADDR3H");
MakeName(0xFEA7,"ADDR3L");
MakeName(0xFEA8,"ADDR4H");
MakeName(0xFEA9,"ADDR4L");
MakeName(0xFEAA,"ADDR5H");
MakeName(0xFEAB,"ADDR5L");
MakeName(0xFEAC,"ADDR6H");
MakeName(0xFEAD,"ADDR6L");
MakeName(0xFEAE,"ADDR7H");
MakeName(0xFEAF,"ADDR7L");

MakeName(0xFEB0,"ADDR8H");
MakeName(0xFEB1,"ADDR8L");
MakeName(0xFEB2,"ADDR9H");
MakeName(0xFEB3,"ADDR9L");
MakeName(0xFEB4,"ADDRAH");
MakeName(0xFEB5,"ADDRAL");
MakeName(0xFEB6,"ADDRBH");
MakeName(0xFEB7,"ADDRBL");
MakeName(0xFEB8,"ADCSR");
MakeName(0xFEB9,"ADCR");


MakeName(0xFEDA,"PACR");
MakeName(0xFEDB,"P67CR");
MakeName(0xFEDC,"ADTRGR");
MakeName(0xFEDE,"IRQFR");
MakeName(0xFEDF,"BCR");

MakeName(0xFEE0,"FLMCR");
MakeName(0xFEE1,"FLM_EBR1");
MakeName(0xFEE2,"FLM_EBR2");
MakeName(0xFEEC,"FLMER");
MakeName(0xFEED,"FLMSR");

MakeName(0xFEF0,"PWM1_TCR");
MakeName(0xFEF1,"PWM1_DTR");
MakeName(0xFEF2,"PWM1_TCNT");
MakeName(0xFEF4,"PWM2_TCR");
MakeName(0xFEF5,"PWM2_DTR");
MakeName(0xFEF6,"PWM2_TCNT");
MakeName(0xFEF8,"PWM3_TCR");
MakeName(0xFEF9,"PWM3_DTR");
MakeName(0xFEFA,"PWM3_TCNT");

MakeName(0xFF00,"INTC_IPRA");
MakeName(0xFF01,"INTC_IPRB");
MakeName(0xFF02,"INTC_IPRC");
MakeName(0xFF03,"INTC_IPRD");
MakeName(0xFF04,"INTC_IPRE");
MakeName(0xFF05,"INTC_IPRF");
MakeName(0xFF08,"DTC_DTEA");
MakeName(0xFF09,"DTC_DTEB");
MakeName(0xFF0A,"DTC_DTEC");
MakeName(0xFF0B,"DTC_DTED");
MakeName(0xFF0C,"DTC_DTEE");
MakeName(0xFF0D,"DTC_DTEF");

MakeName(0xFF10,"WDT__TCSR");
MakeName(0xFF11,"WDT_TCNT");
MakeName(0xFF14,"WSC_WCR");
MakeName(0xFF15,"RAMCR");
MakeName(0xFF16,"BSC_ARBT");
MakeName(0xFF17,"BSC_AR3T");
MakeName(0xFF19,"SYSC_MDCR");
MakeName(0xFF1A,"SYSC_SBYCR");
MakeName(0xFF1B,"SYSC_BRCR");
MakeName(0xFF1C,"SYSC_NMICR");
MakeName(0xFF1D,"SYSC_IRQCR");
MakeName(0xFF1E,"SYSC_writeCR");
MakeName(0xFF1F,"SYSC_RSTCSR");

MakeName(0xFF20,"T1CRH");
MakeName(0xFF21,"T1CRL");
MakeName(0xFF22,"T1SRAH");
MakeName(0xFF23,"T1SRAL");
MakeName(0xFF24,"T1OERA");
MakeName(0xFF25,"TMDRA");
MakeName(0xFF26,"T1CNTH");
MakeName(0xFF27,"T1CNTL");
MakeName(0xFF28,"T1GR1H");
MakeName(0xFF29,"T1GR1L");
MakeName(0xFF2A,"T1GR2H");
MakeName(0xFF2B,"T1GR2L");
MakeName(0xFF2C,"T1DR1H");
MakeName(0xFF2D,"T1DR1L");
MakeName(0xFF2E,"T1DR2H");
MakeName(0xFF2F,"T1DR2L");

MakeName(0xFF30,"TSTR");
MakeName(0xFF31,"T1CRA");
MakeName(0xFF32,"T1SRBH");
MakeName(0xFF33,"T1SRBL");
MakeName(0xFF34,"T1OERB");
MakeName(0xFF35,"TMDRB");
MakeName(0xFF38,"T1GR3H");
MakeName(0xFF39,"T1GR3L");
MakeName(0xFF3A,"T1GR4H");
MakeName(0xFF3B,"T1GR4L");
MakeName(0xFF3C,"T1DR3H");
MakeName(0xFF3D,"T1DR3L");
MakeName(0xFF3E,"T1DR4H");
MakeName(0xFF3F,"T1DR4L");

MakeName(0xFF40,"T2CRH");
MakeName(0xFF41,"T2CRL");
MakeName(0xFF42,"T2SRH");
MakeName(0xFF43,"T2SRL");
MakeName(0xFF44,"T2OER");
MakeName(0xFF46,"T2CNTH");
MakeName(0xFF47,"T2CNTL");
MakeName(0xFF48,"T2GR1H");
MakeName(0xFF49,"T2GR1L");
MakeName(0xFF4A,"T2GR2H");
MakeName(0xFF4B,"T2GR2L");
MakeName(0xFF4C,"T2DR1H");
MakeName(0xFF4D,"T2DR1L");
MakeName(0xFF4E,"T2DR2H");
MakeName(0xFF4F,"T2DR2L");

MakeName(0xFF50,"T3CRH");
MakeName(0xFF51,"T3CRL");
MakeName(0xFF52,"T3SRH");
MakeName(0xFF53,"T3SRL");
MakeName(0xFF54,"T3OER");
MakeName(0xFF56,"T3CNTH");
MakeName(0xFF57,"T3CNTL");
MakeName(0xFF58,"T3GR1H");
MakeName(0xFF59,"T3GR1L");
MakeName(0xFF5A,"T3GR2H");
MakeName(0xFF5B,"T3GR2L");
MakeName(0xFF5C,"T3DR1H");
MakeName(0xFF5D,"T3DR1L");
MakeName(0xFF5E,"T3DR2H");
MakeName(0xFF5F,"T3DR2L");

MakeName(0xFF60,"T4CRH");
MakeName(0xFF61,"T4CRL");
MakeName(0xFF62,"T4SRH");
MakeName(0xFF63,"T4SRL");
MakeName(0xFF64,"T4OER");
MakeName(0xFF66,"T4CNTH");
MakeName(0xFF67,"T4CNTL");
MakeName(0xFF68,"T4GR1H");
MakeName(0xFF69,"T4GR1L");
MakeName(0xFF6A,"T4GR2H");
MakeName(0xFF6B,"T4GR2L");
MakeName(0xFF6C,"T4DR1H");
MakeName(0xFF6D,"T4DR1L");
MakeName(0xFF6E,"T4DR2H");
MakeName(0xFF6F,"T4DR2L");

MakeName(0xFF70,"T5CRH");
MakeName(0xFF71,"T5CRL");
MakeName(0xFF72,"T5SRH");
MakeName(0xFF73,"T5SRL");
MakeName(0xFF74,"T5OER");
MakeName(0xFF76,"T5CNTH");
MakeName(0xFF77,"T5CNTL");
MakeName(0xFF78,"T5GR1H");
MakeName(0xFF79,"T5GR1L");
MakeName(0xFF7A,"T5GR2H");
MakeName(0xFF7B,"T5GR2L");
MakeName(0xFF7C,"T5DR1H");
MakeName(0xFF7D,"T5DR1L");
MakeName(0xFF7E,"T5DR2H");
MakeName(0xFF7F,"T5DR2L");

MakeName(0xFF80,"T6CRH");
MakeName(0xFF81,"T6CRL");
MakeName(0xFF82,"T6SRH");
MakeName(0xFF83,"T6SRL");
MakeName(0xFF84,"T6OER");
MakeName(0xFF86,"T6CNTH");
MakeName(0xFF87,"T6CNTL");
MakeName(0xFF88,"T6GR1H");
MakeName(0xFF89,"T6GR1L");
MakeName(0xFF8A,"T6GR2H");
MakeName(0xFF8B,"T6GR2L");

MakeName(0xFF90,"T7CRH");
MakeName(0xFF91,"T7CRL");
MakeName(0xFF92,"T7SRH");
MakeName(0xFF93,"T7SRL");
MakeName(0xFF94,"T7OER");
MakeName(0xFF96,"T7CNTH");
MakeName(0xFF97,"T7CNTL");
MakeName(0xFF98,"T7GR1H");
MakeName(0xFF99,"T7GR1L");
MakeName(0xFF9A,"T7GR2H");
MakeName(0xFF9B,"T7GR2L");

MakeName(0xFFA0,"MLTCR");
MakeName(0xFFA1,"MLTBR");
MakeName(0xFFA2,"MLTMAR");
MakeName(0xFFA3,"MLTAR");

MakeName(0xFFB0,"MULT_CA");
MakeName(0xFFB1,"MULT_(CA)");
MakeName(0xFFB2,"MULT_CB");
MakeName(0xFFB3,"MULT_(CB)");
MakeName(0xFFB4,"MULT_CC");
MakeName(0xFFB5,"MULT_(CC)");
MakeName(0xFFB6,"MULT_XH");
MakeName(0xFFB7,"MULT_(XH)");
MakeName(0xFFB8,"MULT_H");
MakeName(0xFFB9,"MULT_(H)");
MakeName(0xFFBA,"MULT_L");
MakeName(0xFFBB,"MULT_(L)");
MakeName(0xFFBC,"MULT_MR");
MakeName(0xFFBD,"MULT_(MR)");
MakeName(0xFFBE,"MULT_MMR");
MakeName(0xFFBF,"MULT_(MMR)");













}