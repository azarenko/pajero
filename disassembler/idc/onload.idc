//
//      This IDC file is called after a new file is loaded into IDA
//      database.
//      IDA calls "OnLoad" function from this file.
//
//      You may use this function to read extra information (such as
//      debug information) from the input file, or for anything else.
//

#include <idc.idc>
#include <memcpy.idc>

//      If you want to add your own processing of newly created databases,
//      you may create a file named "userload.idc":
//
//      #define USERLOAD_IDC
//      static userload(input_file,real_file,filetype) {
//              ... your processing here ...
//      }
//

#softinclude <userload.idc>

// Input parameteres:
//      input_file - name of loaded file
//      real_file  - name of actual file that contains the input file.
//                   usually this parameter is equal to input_file,
//                   but is different if the input file is extracted from
//                   an archive.
//      filetype   - type of loaded file. See FT_.. definitions in idc.idc

#define IVT_START 0x0000
#define H8_ROM_START 0x0140
#define H8_CODE_OFFSET 0x10000
#define SH_ROM_START 0x0400
#define M32R_ROM_START 0x0080

static OnLoad(input_file,real_file,filetype)
{
	auto ea, end, ea_rebase, processor, user_message;
#ifdef USERLOAD_IDC             // if user-defined IDC file userload.idc
                                // exists...
    if ( userload(input_file,real_file,filetype) ) return;
#endif
    if ( filetype == FT_DRV )
        DriverLoaded();
        processor = get_processor();
        if (processor == "h8500" || 
            processor == "SH4B"  ||
            processor == "m32rx") 
        {
        	user_message = "Processor " + processor + " is used in Mitsubishi ECUs\nShall IDA perform automatic fixups for Mitsubishi ECU?";
	        if(AskYN(0, user_message) == 1)
	        {	            
		    if ( processor == "h8500" ) {		    

				Message("H8/500 create segment %x-%x\n", 0x10000, 0x1ffff);
				SegCreate(0x10000, 0x1ffff, 0x0, 0, 1, 2);	
				SegRename(0x10000,"seg001"); 
				SegClass (0x10000,"CODE");
				SegDefReg(0x10000,"br",0x0);
				SegDefReg(0x10000,"dp",0x1);		    	   	
				SetSegmentType(0x10000,2);

				//Message("H8/500 create segment %x-%x\n", 0x14000, 0x1ffff);
				//SegCreate(0x14000, 0x20000, 0x0, 0, 1, 2);
				//SegRename(0x14000,"seg001");		        
				//SegClass (0x14000,"CODE");
				//SegDefReg(0x14000,"br",0x0);
				//SegDefReg(0x14000,"dp",0x1);
				//SetSegmentType(0x14000,2);

				Message("H8/500 create segment %x-%x\n", 0x20000, 0x2ffff);
				SegCreate(0x20000, 0x2ffff, 0x0, 0, 1, 2);
				SegRename(0x20000,"seg002");		        
				SegClass (0x20000,"CODE");
				SegDefReg(0x20000,"br",0x0);
				SegDefReg(0x20000,"dp",0x2);
				SetSegmentType(0x20000,2);

					        
				Message("H8/500 Create RAM\n");
				SegCreate(0xEE80, 0xFFFF, 0, 1, saRelWord, 0);
				SegRename(0XEE80,"RAM");

				LowVoids(ea);
				HighVoids(end + H8_CODE_OFFSET);				
			        Message("H8/500 Perform Vector Table Fixups \n");	        	        	                
			        Fixup_VT(0x10000, H8_ROM_START);
			        Message("H8/500 Mitsubishi ECU autonalysis finished.\n");	        		        
		    }
		    if ( processor == "SH4B" ) {	    
		    	  SegCreate(0xFFFF6000, 0xFFFFFFFF, 0, 1, saRelWord, 0);
		    	  Message("ROM (0xFFFF6000 - 0xFFFFFFFF) created...\n");
		    	  FixConstants();
            Wait();
		        Fixup_VT(0x0000, SH_ROM_START);	 
		        Wait(); 
		        FixupJumps();     
		        Wait();
		        Fix_Missing_Code(SH_ROM_START, 0xF20, 1);
		        Fix_Missing_Code(Word(2), SegEnd(Word(2)), 0);
		        Wait();
		        Fix_MUT_Table();
		        Wait();
            FixDataOffsets();
            Wait();
		        Message("SH4B Mitsubishi ECU autonalysis finished\n");
		    }
		    if ( processor == "m32rx" ) {	    	  
			      Fixup_VT_M32R(0x0000, M32R_ROM_START/2+1, 0x10);
			      Fixup_VT_M32R(0x40, M32R_ROM_START+1, 0x4);
		        Message("M32R Vector Table Fixups Performed\n");
		    }    
		}
	}
}


static Fixup_VT_M32R(segoffset, romstart, increment)
{
    auto i;

    // fixup all vector table entries
    for (i = (segoffset + IVT_START); i < (segoffset + romstart); i = i + increment) 
    {
    	if(!MakeCode(i))
    	{
	        MakeDword(i);
	        OpOff(i,0,0);
        }
        else
        {
        	AutoMark(i, AU_PROC );
        	Message("Entry Point Fixups Performed %x...\n",i);
        }
        
    }
}

static Fixup_VT(segoffset, romstart)
{
    auto i, j, errcode;

// fixup all vector table entries
    for (i = (segoffset + IVT_START); i < (segoffset + romstart); i = i + 4 ) {
        MakeDword(i);
        OpOff(i,0,0);
        j = Dword(i);
        errcode = AddEntryPoint(j,j,"",1);
        Message("Entry Point Fixups Performed %x...\n",j);
        MakeCode(j);
        AutoMark(j, AU_PROC );
    }
}


static FixupJumps(void)
{
        auto ea,end,indexa,indexj,xref_from,xref_to; 	

	ea = 0;
	end = SegEnd(ea);
	if (ea == BADADDR || end == BADADDR)
	{
		Message("nothing selected\n");
		return;
	}	
	Message("fixing jmp from %x to %x...\n",ea,end);

	for(ea;ea<=end;ea=NextAddr(ea)) 
	{ 
		if( ea == BADADDR || ea >= end)
		{
			Message("No more hits\n");
			break;
		}	
		else
		{			
			// Check for "mova"
        		if (GetMnem(ea) == "mova")
        		{
        			Message("mova @ %x\n", ea);
        			indexa = NextHead(ea,end) + GetOperandValue(ea, 0);
        			Message("mova initial @ %x\n", indexa);
        			
        			while(Word(indexa) == 0xFFFF)
        			{
        				MakeWord(indexa);
        				indexa = indexa + 2;
        			}
        			Message("mova points to @ %x\n", indexa);
        			do
        			{
        				ea=NextAddr(ea);
        				if (GetMnem(ea) == "jmp")
        				{
        					xref_from = ea;
        					Message("jmp @ %x\n", xref_from);
        					break;
        				}
        					
        			}while (ea != BADADDR);
											
				indexj = indexa;
				while(isUnknown(GetFlags(indexj)))
				{
					MakeWord(indexj);
					xref_to = indexa + Word(indexj);
					MakeCode(xref_to);
					AddCodeXref(xref_from, xref_to, fl_JN);	
					Message("Adding jump from %x to %x\n", xref_from, xref_to);
					MakeComm(indexj, "jsr " + NameEx(indexj, xref_to));					
					indexj = indexj + 2;
					ea  = indexj;
				}
				
			} 
		}
	}   
	Message("fixing jmp finished\n");
}

static Fix_Missing_Code(ea, end, is_byte_check)
{         	
	
	if (ea == BADADDR || end == BADADDR)
	{
		Message("nothing selected\n");
		return;
	}	
	Message("fixing missing code from %x to %x...\n",ea,end);

	for(ea;ea<=end;ea=NextAddr(ea)) 
	{ 
		if( ea == BADADDR || ea >= end)
		{
			Message("No more hits\n");
			break;
		}	
		else
		{			
			if(
				isUnknown(GetFlags(ea))	 &&			
				( is_byte_check ||
				 Byte(ea) == 0x2F ||
				 Byte(ea) == 0x4F )
			  )
			{		
				Message("fixing code at %x\n",ea);	   
				AddEntryPoint(ea,ea,"",1);
				//MakeCode(ea);				
			}
		}
	}   
	Message("fixing missing code finished \n");
}

static Fix_MUT_Table(void)
{
        auto ea,end,i, mutname; 	

	ea = 0;
	end = SegEnd(ea);
	if (ea == BADADDR || end == BADADDR)
	{
		Message("nothing selected\n");
		return;
	}	
	Message("searching for MUT table %x to %x...\n",ea,end);

	for(ea;ea<=end;ea=NextAddr(ea)) 
	{ 
		if( ea == BADADDR || ea >= end)
		{
			Message("No more hits\n");
			break;
		}	
		else
		{			
			// Check for "mov.w"
        		if (GetMnem(ea) == "mov.w")
        		{
        			if (
        				Word(NextHead(NextHead(ea,end) + GetOperandValue(ea, 0),end)) == 0xBF &&
        				GetMnem(ea+6) == "shll2"
        			   )
        			{                      
        			    ea = Dword(NextAddr(NextAddr(ea+8) + GetOperandValue(ea+8, 0)));
        			    Message("MUT @ 0x%x\n", ea);
        			    break;
				}				
			} 
		}
	}   
	
	i = 0;
	for(ea;ea<=end;ea=ea + 4) 
	{ 
		if (ea == BADADDR || end == BADADDR)
		{
			Message("No more matches...\n");
			return;
		}
		if (Dword(ea) != 0xFFFFFFFF)
		{
			MakeDword(ea);	
			mutname = form("MUT_%X",i++);	
			Message("fixing " + mutname + "\n");
			MakeName(Dword(ea),mutname);
		}
		else
			break;
			
	}
	Message("fixing MUT finished \n");
}

static FixDataOffsets(void)
{
        auto ea,end,disass; 	

	ea = 0;
	end = SegEnd(ea);
	if (ea == BADADDR || end == BADADDR)
	{
		Message("nothing selected\n");
		return;
	}	
	Message("fixing offsets from %x to %x...\n",ea,end);

	for(ea;ea<=end;ea=NextAddr(ea)) 
	{ 
		if( ea == BADADDR || ea >= end)
		{
			Message("No more hits\n");
			break;
		}	
		else
		{			
			// Check for loc_, off_xxx + y
			disass = GetDisasm(ea);
		
        			if 
			(
				(strstr(disass ,".data.l loc_") != -1 && strstr(disass ,"+") != -1) ||
				(strstr(disass ,".data.l off_") != -1 && strstr(disass ,"+") != -1)
			)
        			{
        				Message("fixing %s  @0x%x\n", disass, ea);
				MakeWord(ea);
			}
		}
	}   
	Message("fixing off_****, loc_**** finished\n");
}

static FixConstants(void)
{
        auto ea,end,disass; 	

	ea = 0x1500;
	end = 0x3500;
		
	Message("fixing constants from %x to %x...\n",ea,end);

	for(ea;ea<=end;ea=NextAddr(ea)) 
	{ 
		if( ea == BADADDR || ea >= end)
		{
			Message("No more hits\n");
			break;
		}	
		else
		{	
      Message("fixing constant  @0x%x\n", ea);		
			MakeWord(ea);			
		}
	}   
	Message("fixing constants finished\n");
}

//-----------------------------------------------------------------------
// Get name of the current processor

// usually, we don't use this function now...
static get_processor(void) {
  auto i,procname,chr;

  procname = "";
  for ( i=0; i < 8; i++ ) {
    chr = GetCharPrm(INF_PROCNAME+i);
    if ( chr == 0 ) break;
    procname = procname + chr;
  }
  return procname;
}


//--------------------------------------------------------------------------
//      This function is executed when a new device driver is loaded.
//              Device drivers have extensions DRV or SYS.
//
// History:
//
// 08/12/95 20:16 by Alexey Kulentsov:
// + Check for Device Request Block
// + Kludge with Drv/Com supported
// 04/01/96 04:21 by ig:
// + 0000:0000 means end of devices chain too.
// 16/05/96 16:01 by ig:
// + modified to work with the new version of IDA (separate operand types)

static DriverLoaded(void) {
  auto x,i,base;
  auto intr,strt;
  auto attr,cmt;
  auto nextbase;
  auto DevReq;

  i = 0;
  x = MinEA();
  base = (x >> 4);   // The segment base

  while ( 1 ) {
    Message("Device driver block at %04X\n",x);

    MakeName(x,form("NextDevice_%ld",i));
    MakeWord(x);
    OpNumber(x,0);
    if ( Word(x) == 0xFFFF ) {
      MakeComm(x,"The last device");
    } else {
      nextbase = base + Word(x+2);
      OpOff(x,0,[nextbase,0]);
      MakeComm(x,"Offset to the next device");
    }

    MakeWord(x+2);
    OpNumber(x+2,0);

    MakeName(x+4,form("DevAttr_%ld",i));
    MakeWord(x+4);
    OpNumber(x+4,0);
    attr = Word(x+4);
    cmt = "";
    if ( attr & (1<< 0) ) cmt = cmt + "stdin device\n";
    if ( attr & (1<< 1) ) cmt = cmt + ((attr & (1<<15)) ? "stdout device\n" : ">32M\n");
    if ( attr & (1<< 2) ) cmt = cmt + "stdnull device\n";
    if ( attr & (1<< 3) ) cmt = cmt + "clock device\n";
    if ( attr & (1<< 6) ) cmt = cmt + "supports logical devices\n";
    if ( attr & (1<<11) ) cmt = cmt + "supports open/close/RM\n";
    if ( attr & (1<<13) ) cmt = cmt + "non-IBM block device\n";
    if ( attr & (1<<14) ) cmt = cmt + "supports IOCTL\n";
    cmt = cmt + ((attr & (1<<15)) ? "character device" : "block device");
    MakeComm(x+4,cmt);

    MakeName(x+6,form("Strategy_%ld",i));
    MakeWord(x+6);
    OpOff(x+6,0,MinEA());

    MakeName(x+8,form("Interrupt_%ld",i));
    MakeWord(x+8);
    OpOffset(x+8,MinEA());

    MakeName(x+0xA,form("DeviceName_%ld",i));
    MakeStr (x+0xA,8);
    MakeComm(x+0xA,"May be device number");

    strt = [ base, Word(x+6) ];
    intr = [ base, Word(x+8) ];
    MakeCode( strt );
    MakeCode( intr );
    AutoMark( strt, AU_PROC );
    AutoMark( intr, AU_PROC );
    MakeName( strt, form("Strategy_Routine_%ld",i));
    MakeName( intr, form("Interrupt_Routine_%ld",i));
    MakeComm( strt, "ES:BX -> Device Request Block");
    MakeComm( intr, "Device Request Block:\n"
          "0 db length\n"
      "1 db unit number\n"
      "2 db command code\n"
      "5 d? reserved\n"
      "0D d? command specific data");

    if( Byte( strt )==0x2E && Word(strt+1)==0x1E89
     && Byte(strt+5)==0x2E && Word(strt+6)==0x068C
     && Word(strt+3)==Word(strt+8)-2)
    {
     DevReq=Word(strt+3);
     Message("DevReq at %x\n",DevReq);
     MakeUnkn(x+DevReq,0);MakeUnkn(x+DevReq+2,0);
     MakeDword(x+DevReq);MakeName(x+DevReq,form("DevRequest_%ld",i));
    }

    if ( Word(x) == 0xFFFF ||
       ((Byte(x)==0xE9 || Byte(x)==0xEB) && i==0) ) break;
    if ( Dword(x) == 0 ) break; // 04.01.96
    x = [ nextbase, Word(x) ];
    i = i + 1;
  }
}
