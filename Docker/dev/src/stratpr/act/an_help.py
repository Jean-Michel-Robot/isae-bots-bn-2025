#!/usr/bin/env python
# -*- coding: utf-8 -*-
#     ____                                                  
#    / ___| _   _ _ __   __ _  ___ _ __ ___                 
#    \___ \| | | | '_ \ / _` |/ _ \ '__/ _ \                
#     ___) | |_| | |_) | (_| |  __/ | | (_) |               
#    |____/ \__,_| .__/ \__,_|\___|_|  \___/                
#   ____       _ |_|       _   _ _       ____ _       _     
#  |  _ \ ___ | |__   ___ | |_(_) | __  / ___| |_   _| |__  
#  | |_) / _ \| '_ \ / _ \| __| | |/ / | |   | | | | | '_ \ 
#  |  _ < (_) | |_) | (_) | |_| |   <  | |___| | |_| | |_) |
#  |_| \_\___/|_.__/ \___/ \__|_|_|\_\  \____|_|\__,_|_.__/ 

# pyright: reportMissingImports=false

#################################################################
#                                                               #
#                           IMPORTS                             #
#                                                               #
#################################################################

import rospy
import an_ctse

#################################################################
#                                                               #
#                          CONSTANTS                            #
#                                                               #
#################################################################

def log_info(log):
    """
    Print standard logs.
    """
    rospy.loginfo(f"{an_ctse._NODENAME_} {log}")


def log_warn(log):
    """
    Print warning logs.
    """
    rospy.logwarn(f"{an_ctse._NODENAME_} {log}")

def log_errs(log):
    """
    Print errors logs.
    """
    rospy.logerr(f"{an_ctse._NODENAME_} {log}")