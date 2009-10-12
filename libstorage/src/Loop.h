/*
 * Copyright (c) [2004-2009] Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#ifndef LOOP_H
#define LOOP_H

#include "y2storage/Volume.h"

namespace storage
{
class LoopCo;
class ProcPart;

class Loop : public Volume
    {
    public:
	Loop( const LoopCo& d, const string& LoopDev, const string& LoopFile,
	      bool dmcrypt, const string& dm_dev,
	      ProcPart& ppart, SystemCmd& losetup );
	Loop( const LoopCo& d, const string& file, bool reuseExisting,
	      unsigned long long sizeK, bool dmcr );
	Loop( const LoopCo& d, const Loop& rhs );
	virtual ~Loop();
	const string& loopFile() const { return lfile; }
	void setLoopFile( const string& file );
	bool getReuse() { return( reuseFile ); }
	void setReuse( bool reuseExisting );
	void setDelFile( bool val=true ) { delFile=val; }
	bool removeFile();
	bool createFile();
	string lfileRealPath() const;
	void setDmcryptDev( const string& dm_dev, bool active=true );
	friend std::ostream& operator<< (std::ostream& s, const Loop& l );

	virtual void print( std::ostream& s ) const { s << *this; }
	virtual int setEncryption( bool val, storage::EncryptType typ=storage::ENC_LUKS );

	string removeText( bool doing ) const;
	string createText( bool doing ) const;
	string formatText( bool doing ) const;

	void getInfo( storage::LoopInfo& info ) const;
	bool equalContent( const Loop& rhs ) const;
	void logDifference( const Loop& d ) const;
	static unsigned major();
	static string loopDeviceName( unsigned num );

	static bool notDeleted( const Loop& l ) { return( !l.deleted() ); }

    protected:
	void init();
	void checkReuse();
	static void getLoopMajor();
	Loop& operator=( const Loop& );

	string lfile;
	bool reuseFile;
	bool delFile;

	static unsigned loop_major;
	mutable storage::LoopInfo info;
    };

}

#endif
