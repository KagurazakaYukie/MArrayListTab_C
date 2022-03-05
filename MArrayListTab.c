#include <stdlib.h>
#include "MArrayListTab.h"
#include "Init.h"
#include "MArrayList.h"
#include "MultitThreadMemoryManager.h"

MArrayListTab *MArrayListTabCreate(MTMemoryManager *mm, MArrayList *arrayList) {
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = arrayList;
    malt->mark = MArrayListInit(mm);
    for (int i = 0; i < MArrayListSize(arrayList); ++i) {
        MArrayListAddIndex(mm, malt->mark, MTMemoryManagerCalloc(mm, sizeof(int)));
    }
    malt->markindex = MArrayListInit(mm);
    return malt;
}

MArrayListTab *MArrayListTabInit(MTMemoryManager *mm) {
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = MArrayListInit(mm);
    malt->mark = MArrayListInit(mm);
    malt->markindex = MArrayListInit(mm);
    return malt;
}

void MArrayListTabDestroy(MTMemoryManager *mm) {
    MArrayListDestroy(mm,malt->al);
    MArrayListDestroy(mm,malt->mark);
    MArrayListDestroy(mm,malt->markindex);
    MTMemoryManagerFree(mm,malt->mi);
}

void MBUArrayListTabDestroy(MemoryBigUnit *mbu) {
    MBUArrayListDestroy(mbu,malt->al);
    MBUArrayListDestroy(mbu,malt->mark);
    MBUArrayListDestroy(mbu,malt->markindex);
    MTMemoryManagerUnitFree(mbu,malt->mi);
}

void MarrayListTabAddIndex(MTMemoryManager *mm, MArrayListTab *lt, void *m) {
    if (lt->markindex->length) {
        unsigned long i = *((unsigned long *) ((MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1])->m);
        lt->al->Element[i] = m;
        *((int *) ((MemoryInfo *) lt->mark->Element[i])->m) = 0;
        MTMemoryManagerFree(mm, (MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1]);
        lt->markindex->length--;
    } else {
        MArrayListAddIndex(mm, lt->al, m);
        MArrayListAddIndex(mm, lt->mark, MTMemoryManagerCalloc(mm, sizeof(int)));
    }
}

void MArrayListTabMark(MTMemoryManager *mm, MArrayListTab *listTab, DataSizeType index) {
    *((int *) ((MemoryInfo *) listTab->mark->Element[index])->m) = 1;
    MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(unsigned long));
    *((unsigned long *) mi->m) = index;
    MArrayListAddIndex(mm, listTab->markindex, mi);
}

void MArrayListTabMarks(MTMemoryManager *mm, MArrayListTab *listTab, unsigned long *index,unsigned long len) {
    for (int i = 0; i < len; ++i) {
        *((int *) ((MemoryInfo *) listTab->mark->Element[index[i]])->m) = 1;
        MemoryInfo *mi = MTMemoryManagerCalloc(mm, sizeof(unsigned long));
        *((unsigned long *) mi->m) = index[i];
        MArrayListAddIndex(mm, listTab->markindex, mi);
    }
}

MArrayListTab *MBUArrayListTabCreate(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayList *arrayList) {
    MemoryInfo *mi = MTMemoryManagerUnitCalloc(mm, mbu, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = arrayList;
    malt->mark = MBUArrayListInit(mm, mbu);
    for (int i = 0; i < MArrayListSize(arrayList); ++i) {
        MArrayListAddIndex(mm, malt->mark, MTMemoryManagerUnitCalloc(mm, mbu, sizeof(int)));
    }
    malt->markindex = MBUArrayListInit(mm, mbu);
    return malt;
}

MArrayListTab *MBUArrayListTabInit(MTMemoryManager *mm, MemoryBigUnit *mbu) {
    MemoryInfo *mi = MTMemoryManagerUnitCalloc(mm, mbu, sizeof(MArrayListTab));
    MArrayListTab *malt = (MArrayListTab *) mi->m;
    malt->mi = mi;
    malt->al = MBUArrayListInit(mm, mbu);
    malt->mark = MBUArrayListInit(mm, mbu);
    malt->markindex = MBUArrayListInit(mm, mbu);
    return malt;
}

void MBUarrayListTabAddIndex(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *lt, void *m) {
    if (lt->markindex->length) {
        unsigned long i = *((unsigned long *) ((MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1])->m);
        lt->al->Element[i] = m;
        *((int *) ((MemoryInfo *) lt->mark->Element[i])->m) = 0;
        MTMemoryManagerUnitFree(mbu, (MemoryInfo *) lt->markindex->Element[lt->markindex->length - 1]);
        lt->markindex->length--;
    } else {
        MArrayListAddIndex(mm, lt->al, m);
        MArrayListAddIndex(mm, lt->mark, MTMemoryManagerUnitCalloc(mm,mbu, sizeof(int)));
    }
}

void MBUArrayListTabMark(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *listTab, DataSizeType index) {
    *((int *) ((MemoryInfo *) listTab->mark->Element[index])->m) = 1;
    MemoryInfo *mi = MTMemoryManagerUnitCalloc(mm, mbu, sizeof(unsigned long));
    *((unsigned long *) mi->m) = index;
    MArrayListAddIndex(mm, listTab->markindex, mi);
}

void MBUArrayListTabMarks(MTMemoryManager *mm, MemoryBigUnit *mbu, MArrayListTab *listTab, unsigned long *index,unsigned long len) {
    for (int i = 0; i < len; ++i) {
        *((int *) ((MemoryInfo *) listTab->mark->Element[index[i]])->m) = 1;
        MemoryInfo *mi = MTMemoryManagerUnitCalloc(mm, mbu, sizeof(unsigned long));
        *((unsigned long *) mi->m) = index[i];
        MArrayListAddIndex(mm, listTab->markindex, mi);
    }
}

void *MArrayListTabGetIndex(MArrayListTab *listTab, DataSizeType index) {
    if (*((int *) ((MemoryInfo *) listTab->mark->Element[index])->m)) {
        return NULL;
    }
    return listTab->al->Element[index];
}

unsigned long MArrayListTabSize(MArrayListTab *alt) {
    return alt->al->length;
}

