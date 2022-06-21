#!/bin/csh -f

# absolute path here:
set base = /gig48/patrick/feret/final_release
# relative path here:
# set base = ../



set master_coords_file = $base/data/misc/coords.3816
set bin = $base/bin

set images_raw = inp
set images_norm = out
set coords = $images_raw/coords.some_fa

goto 2
2:


#    select and prepare some suitable images
#
#
rm -rf $images_raw && mkdir $images_raw
find $base/data/cd_one/images -name \*fa\* | head -300 >  use
find $base/data/cd_two/images -name \*fa\* | head -300 >> use
rm -f $coords
foreach i (`cat use`)
   set s = $i:t
   set t = $s:r
   set j = $t:r
   bzip2 -cd $i > $j
   convert -quality 95  $j JPG:$images_raw/$j.jpg && rm $j
   grep $j:r $master_coords_file | \
      awk '{printf("%s.jpg %s %s %s %s\n", $1, $2,$3,$4,$5)}' >> $coords
end
rm -f use




#    do the image normalization
#
#
rm -rf $images_norm && mkdir $images_norm
$bin/face2norm  $coords  $images_raw/ $images_norm/




#    form the sample and covariance matrix
#
#
set samples = sample_images.mat
set covar = $samples.cov
$bin/norm2samp    $samples $images_norm/*fa*
$bin/samp2cova -i $samples




#    finally produce find the top few eigenvectors
#
#
$bin/cova2eigv -n 128 -s $samples $covar

1:
set samples = sample_images.mat
set covar = $samples.cov


#    now use the eigenvectors in a recognition engine
rm -rf sim && mkdir sim
ls -1 $images_norm > gallery.names
ls -1 $images_norm > probe.names
$bin/eigen_recog_MANG -f 2 -n 126 $covar.{evt,eva} $samples.mean {gallery,probe}.names sim $images_norm


# tidy up a little, the sample matrix is big
rm $samples

# make a viewable sun raster out of the covariance matrix
$bin/ihdr2sun $covar
