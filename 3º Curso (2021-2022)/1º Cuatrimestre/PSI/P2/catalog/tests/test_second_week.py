"""
Second Week Tests
Created by JAMI
EPS-UAM 2021
"""

from django.test import TestCase
from django.urls import reverse
from django.contrib.staticfiles import finders


class SecondWeekTests(TestCase):
    @classmethod
    def setUpTestData(cls):
        # Set up non-modified objects used by all test methods
        try:
            from populate_catalog import populate
            populate()
        except ImportError:
            print('The module populate_catalog does not exist')
        except NameError:
            print('The function populate() does not exist or is not correct')
        except Exception:
            print('Something went wrong in the populate() function :-(')
            raise


    def test_new_added_book_visualizations(self):
        from catalog.admin import BooksInstanceInline as bii
        from catalog.admin import BookAdmin as ba
        from catalog.admin import BookInstanceAdmin as bia
        self.assertEqual(bii.extra,0)
        self.assertEqual(ba.inlines[0],bii)
        lf = ('status', 'due_back')
        self.assertEqual(bia.list_filter,lf)


    def test_book_class_additions(self):
        from catalog.models import Book
        self.assertTrue('display_genre' in str(Book.display_genre))
        self.assertEqual(Book.display_genre.short_description,'Genre')


    def test_new_added_author_admin(self):
        from catalog.admin import AuthorAdmin as aa
        ld = ('last_name', 'first_name', 'date_of_birth', 'date_of_death')
        f  = ['first_name', 'last_name', ('date_of_birth', 'date_of_death')]
        self.assertTrue(ld == aa.list_display)
        self.assertTrue(f  == aa.fields)


    def test_challenge_part4_one(self):
        from catalog.admin import BookInstanceAdmin as bia
        ld = ('book', 'status', 'due_back', 'id')
        self.assertTrue(ld[0] == bia.list_display[0])
        self.assertTrue(ld[1] == bia.list_display[1])


    def test_challenge_part4_two(self):
        from catalog.admin  import AuthorAdmin as aa
        from catalog.admin  import BooksInline as bil
        from catalog.models import Book as bo
        self.assertTrue(aa.inlines[0] == bil)
        self.assertTrue(bil.model == bo)
        self.assertEqual(bil.extra,0)


    def test_static_file_css(self):
        result = finders.find('css/styles.css')
        self.assertIsNotNone(result)


    def test_index_using_template(self):
        response = self.client.get(reverse('index'))
        self.assertTemplateUsed(response, 'index.html')


    def test_incex_contains_message(self):
        response = self.client.get(reverse('index'))
        self.assertIn(b'The library has the following record counts:', response.content)


    def test_challenge_part5_one(self):
        response = self.client.get(reverse('index'))
        self.assertIn(b'<title>', response.content)
        self.assertIn(b'</title>', response.content)


    def test_challenge_part5_two(self):
        response = self.client.get(reverse('index'))
        self.assertIn(b'Genres:', response.content)  # Fix this in your code
        self.assertIn(b"Books containing the letter 'a' in the title:", response.content) # Fix this in your code


    def test_book_list(self):
        response = self.client.get(reverse('books'))
        self.assertIn(b'Cementerio de Animales', response.content)
        self.assertIn(b'I Robot', response.content)
        self.assertIn(b'Page 1 of 2', response.content)


    def test_book_detail(self):
        from catalog.models import Book
        #book = Book.objects.get(id=1)
        book = Book.objects.filter(title__contains='The Shining').first()
        response = self.client.get(book.get_absolute_url())
        self.assertIn(b'9780345806789', response.content)


    def test_challenge_part6_one(self):
        response = self.client.get(reverse('authors'))
        self.assertIn(b'Asimov, Isaac', response.content)
        self.assertIn(b'King, Stephen', response.content)


    def test_challenge_part6_two(self):
        from catalog.models import Author
        #author = Author.objects.get(id=1)
        author = Author.objects.filter(last_name__contains='King').first()
        response = self.client.get(author.get_absolute_url())
        self.assertIn(b'Louis Creed', response.content)


    def test_challenge_part6_three(self):
        from catalog.models import Author
        #author = Author.objects.get(id=1)
        author = Author.objects.filter(last_name__contains='Asimov').first()
        response = self.client.get(author.get_absolute_url())
        #response = self.client.get(reverse('author-detail', kwargs={'pk': 2}))
        self.assertIn(b'American writer Isaac Asimov', response.content)
