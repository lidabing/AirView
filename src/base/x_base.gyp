#Copyright(c)2013 The AirView Authors.All rights reserved.
#Use of this source code is governed by a BSD - style license that can be
#found in the LICENSE file.

{
  'targets' :[
               {
                 'target_name' : 'x_base',
                 'type' : 'none',
                 'includes' :[ 'x_base.gypi', ],
                 'sources/' :[ [ 'exclude', '.*' ], ],
               },
             ]
}