/*****************************************************************
|
|    AP4 - Synthetic Sample Table
|
|    Copyright 2003-2005 Gilles Boccon-Gibod & Julien Boeuf
|
|
|    This file is part of Bento4/AP4 (MP4 Atom Processing Library).
|
|    Unless you have obtained Bento4 under a difference license,
|    this version of Bento4 is Bento4|GPL.
|    Bento4|GPL is free software; you can redistribute it and/or modify
|    it under the terms of the GNU General Public License as published by
|    the Free Software Foundation; either version 2, or (at your option)
|    any later version.
|
|    Bento4|GPL is distributed in the hope that it will be useful,
|    but WITHOUT ANY WARRANTY; without even the implied warranty of
|    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|    GNU General Public License for more details.
|
|    You should have received a copy of the GNU General Public License
|    along with Bento4|GPL; see the file COPYING.  If not, write to the
|    Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
|    02111-1307, USA.
|
 ****************************************************************/

/*----------------------------------------------------------------------
|   includes
+---------------------------------------------------------------------*/
#include "Ap4Types.h"
#include "Ap4Atom.h"
#include "Ap4SyntheticSampleTable.h"
#include "Ap4Sample.h"

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::AP4_SyntheticSampleTable()
+---------------------------------------------------------------------*/
AP4_SyntheticSampleTable::AP4_SyntheticSampleTable(AP4_Cardinal chunk_size) :
    m_ChunkSize(chunk_size?chunk_size:AP4_SYNTHETIC_SAMPLE_TABLE_DEFAULT_CHUNK_SIZE)
{
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::~AP4_SyntheticSampleTable()
+---------------------------------------------------------------------*/
AP4_SyntheticSampleTable::~AP4_SyntheticSampleTable()
{
    m_SampleDescriptions.DeleteReferences();
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSample
+---------------------------------------------------------------------*/
AP4_Result
AP4_SyntheticSampleTable::GetSample(AP4_Ordinal sample_index, AP4_Sample& sample)
{
    if (sample_index >= m_Samples.ItemCount()) return AP4_ERROR_OUT_OF_RANGE;

    sample = m_Samples[sample_index];
    return AP4_SUCCESS;
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSampleCount
+---------------------------------------------------------------------*/
AP4_Cardinal 
AP4_SyntheticSampleTable::GetSampleCount()
{
    return m_Samples.ItemCount();
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSampleChunkPosition
+---------------------------------------------------------------------*/
AP4_Result   
AP4_SyntheticSampleTable::GetSampleChunkPosition(
    AP4_Ordinal  sample_index, 
    AP4_Ordinal& chunk_index,
    AP4_Ordinal& position_in_chunk)
{
    // default values
    chunk_index       = 0;
    position_in_chunk = 0;
    
    // check parameters
    if (sample_index >= m_Samples.ItemCount()) return AP4_ERROR_OUT_OF_RANGE;
    if (m_ChunkSize == 0) return AP4_ERROR_INVALID_STATE;
    
    // compute in which chunk this sample falls
    chunk_index       = sample_index/m_ChunkSize;
    position_in_chunk = sample_index%m_ChunkSize;
    
    return AP4_SUCCESS;
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSampleDescriptionCount
+---------------------------------------------------------------------*/
AP4_Cardinal 
AP4_SyntheticSampleTable::GetSampleDescriptionCount()
{
    return m_SampleDescriptions.ItemCount();
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSampleDescription
+---------------------------------------------------------------------*/
AP4_SampleDescription* 
AP4_SyntheticSampleTable::GetSampleDescription(AP4_Ordinal index)
{
    AP4_SampleDescription* description;
    if (AP4_SUCCEEDED(m_SampleDescriptions.Get(index, description))) {
        return description;
    } else {
        return NULL;
    }
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::AddSampleDescription
+---------------------------------------------------------------------*/
AP4_Result 
AP4_SyntheticSampleTable::AddSampleDescription(AP4_SampleDescription* description)
{
    return m_SampleDescriptions.Add(description);
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::AddSample
+---------------------------------------------------------------------*/
AP4_Result 
AP4_SyntheticSampleTable::AddSample(AP4_ByteStream& data_stream,
                                    AP4_Position    offset,
                                    AP4_Size        size,
                                    AP4_Ordinal     description_index,
                                    AP4_TimeStamp   cts,
                                    AP4_TimeStamp   dts,
                                    bool            /* sync */)
{
    AP4_Sample sample(data_stream, offset, size, description_index, dts, cts-dts);
    return m_Samples.Append(sample);
}

/*----------------------------------------------------------------------
|   AP4_SyntheticSampleTable::GetSampleIndexForTimeStamp
+---------------------------------------------------------------------*/
AP4_Result 
AP4_SyntheticSampleTable::GetSampleIndexForTimeStamp(AP4_TimeStamp /* ts */, 
                                                     AP4_Ordinal&  /* index */)
{
    return AP4_ERROR_NOT_SUPPORTED;
}
