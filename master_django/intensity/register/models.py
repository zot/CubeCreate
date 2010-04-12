
# Copyright 2010 Alon Zakai ('kripken'). All rights reserved.
# This file is part of Syntensity/the Intensity Engine, an open source project. See COPYING.txt for licensing.

from django.db import models


class SignupForNotify(models.Model):
    email = models.EmailField()

