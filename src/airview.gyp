# Copyright (c) 2013 The AirView Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.
{
'targets':
   [
   {
		'target_name': 'binary',
		'type': 'none',
		'includes': [
            'binary/binary.gypi',
          ],
		   'copies': [
				{
        'destination': '<(PRODUCT_DIR)',
          'files': [
					'binary/master_preferences',
					'binary/gcswf32.dll',
               ]
                },
              ],
	},		
   ],
}