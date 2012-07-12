
/**
   MiracleGrue - Model Generator for toolpathing. <http://www.grue.makerbot.com>
   Copyright (C) 2011 Far McKon <Far@makerbot.com>, Hugo Boyer (hugo@makerbot.com)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU Affero General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

 */


#ifndef REGIONER_H_
#define REGIONER_H_ (1)

#include "slicer.h"
#include "slicer_loops.h"
#include "loop_path.h"

namespace mgl {

class LayerRegions {
public:
	std::list<LoopList> insetLoops;
	LoopList supportLoops;
	LoopList interiorLoops;

	GridRanges flatSurfaces; // # number of slices + roofCount * 2
	GridRanges roofings;
	GridRanges floorings;
	GridRanges supports;

	GridRanges infills;

	GridRanges solids;
	GridRanges sparses;

	size_t layerMeasureId;
};

typedef vector<LayerRegions> RegionList;

//// Class to calculate regions of a model
///

class Regioner : public Progressive {
	Scalar roofLengthCutOff;
public:
	SlicerConfig slicerCfg;


	Regioner(const SlicerConfig &slicerCfg,
			ProgressBar *progress = NULL);

	void generateSkeleton(const Tomograph& tomograph, Regions &regions);
	void generateSkeleton(const LayerLoops& layerloops, Regions &regions);

	void insetsForSlice(const libthing::SegmentTable &sliceOutlines,
			libthing::Insets &sliceInsets,
			const char* scadFile = NULL);
	void insetsForSlice(const LoopList& sliceOutlines,
			std::list<LoopList>& sliceInsets,
			const char* scadFile = NULL);

	void insets(const LayerLoops& outlinesLoops, 
			std::vector<std::list<LoopList> >& insets);

	void flatSurfaces(const std::vector<std::list<LoopList> >& insets,
			const Grid & grid,
			std::vector<GridRanges> & gridRanges);

	void floorForSlice(const GridRanges & currentSurface, 
			const GridRanges & surfaceBelow, 
			const Grid & grid,
			GridRanges & flooring);

	void roofing(const std::vector<GridRanges> & flatSurfaces, 
			const Grid & grid, 
			std::vector<GridRanges> & roofings);
	void roofForSlice(const GridRanges & currentSurface, 
			const GridRanges & surfaceAbove, 
			const Grid & grid, 
			GridRanges & roofing);
	void flooring(const std::vector<GridRanges> & flatSurfaces, 
			const Grid & grid, 
			std::vector<GridRanges> & floorings);
	void infills(const std::vector<GridRanges> &flatSurfaces,
			const Grid &grid,
			const std::vector<GridRanges> &roofings,
			const std::vector<GridRanges> &floorings,
			std::vector<GridRanges> &solids,
			std::vector<GridRanges> &sparses,
			std::vector<GridRanges> &infills);
	void gridRangesForSlice(const std::list<LoopList>& allInsetsForSlice, 
			const Grid& grid, 
			GridRanges& surface);

private:




};

}

#endif /* SKELETOR_H_ */
