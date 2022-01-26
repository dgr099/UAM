"""
Third Week Tests
Created by JAMI
EPS-UAM 2021
"""

from django.test import TestCase
from django.urls import reverse
from django.contrib.auth.models import User, Permission
from catalog.models import Book, BookInstance

user = "user1"
password = "biblioteca"
email = "user@user.es"


class ThirdWeekTests(TestCase):
    @classmethod
    def setUpTestData(cls):
        # Set up non-modified objects used by all test methods
        try:
            from populate_catalog import populate
            populate()
            User.objects.create_user(user, email, password)
        except ImportError:
            print('The module populate_catalog does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except Exception:
            print('Something went wrong :-(')
            raise


    def test_number_of_visits(self):
        response = self.client.get(reverse('index'))
        self.assertIsNotNone(self.client.session['num_visits'])
        self.assertIn(b'You have visited this page', response.content)


    def test_login(self):
        response = self.client.get(reverse('logout'), follow=True)
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)
        self.assertEqual(response.status_code, 200)  # redirection
        self.assertIn(b'Home', response.content)
        self.assertIn(b'All books', response.content)
        self.assertIn(b'All authors', response.content)
        self.assertIn(b'Login', response.content)
        self.assertNotIn(b'Logout', response.content)
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)  # follow redirection
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('index'), follow=True)
        self.assertIn(b'Logout', response.content)
        self.assertIn(b'My Borrowed', response.content)
        self.assertNotIn(b'Login', response.content)


    def test_borrowed(self):
        u  = User.objects.get(username=user)
        bi = BookInstance.objects.filter(book__title='The Shining', status__contains='o').first()
        bi.borrower = u
        bi.save()
        self.test_login()
        response = self.client.get(reverse('my-borrowed'), follow=True)
        self.assertIn(b'The Shining', response.content)


    def test_challenge_part8(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        bi = BookInstance.objects.filter(book__title='The Shining').first()
        bi.borrower = u
        bi.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        self.assertIn(b'Staff', response.content)
        self.assertIn(b'All borrowed', response.content)
        response = self.client.get(reverse('all-borrowed'), follow=True)
        self.assertIn(b'user1', response.content)


    def test_aurhor_form(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        authorDict = {}
        authorDict["first_name"] = 'Julio'
        authorDict["last_name"] = 'Verne'
        authorDict["birth_date"] = '1928-02-08'
        authorDict["die_date"] = '1905-03-24'
        response = self.client.post(reverse('author-create'), authorDict, follow=True)
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Author: Verne, Julio', response.content)


    def test_challenge_part9_one(self):
        u  = User.objects.get(username=user)
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        response = self.client.get(reverse('book-create'), follow=True)
        self.assertEqual(response.status_code, 403)
        bi = Book.objects.filter(title__contains='The Shining').first()
        response = self.client.get(reverse('book-update', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 403)
        response = self.client.get(reverse('book-delete', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 403)


    def test_challenge_part9_two(self):
        u  = User.objects.get(username=user)
        u.is_staff = True
        permission = Permission.objects.get(codename='can_mark_returned')
        u.user_permissions.add(permission)
        u.save()
        loginDict = {}
        loginDict["username"] = user
        loginDict["password"] = password
        response = self.client.post(reverse('login'), loginDict, follow=True)
        response = self.client.get(reverse('book-create'), follow=True)
        self.assertEqual(response.status_code, 200)
        bi = Book.objects.filter(title__contains='The Shining').first()
        response = self.client.get(reverse('book-update', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 200)
        response = self.client.get(reverse('book-delete', kwargs={'pk': bi.pk}))
        self.assertEqual(response.status_code, 200)
